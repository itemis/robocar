/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 2019 initial Contribution
 */

#include "Streamer.h"
#include <unistd.h>
#include <iostream>
#include <ext/stdio_filebuf.h>
#include <fmt/format.h>
#include <iomanip>

#include "spdlog/spdlog.h"

std::string cmd = "/usr/bin/ffmpeg";
char* arg_v[] = { "ffmpeg", "-f", "rawvideo", "-pixel_format", "bgr24",
		"-video_size", "1912x796", "-re", "-framerate", "20", "-i", "-", "-f",
		"rtp", "-preset", "ultrafast", "-c:v", "libx264",
		"rtp://127.0.0.1:41954", nullptr };

std::string o_args =
		"ffmpeg -f rawvideo -pixel_format bgr24 -video_size {0}x{1} -re -framerate 20 -i - -f rtp_mpegts -preset ultrafast -c:v libx264 {2}";
#define SIZE_ARG 6
#define URI_ARG 18

Streamer::Streamer() {
	spdlog::set_level(spdlog::level::debug);
	spdlog::debug("Streamer constructor");

	auto size = fmt::format("{0}x{1}", 320, 200);
	auto uri = fmt::format("rtp://{0}", "127.0.0.1:41954");
//	auto uri = fmt::format("movie.mp4");
	arg_v[SIZE_ARG] = strdup(size.c_str());
	arg_v[URI_ARG] = strdup(uri.c_str());

}

Streamer::~Streamer() {
	close(p_fd1[1]);
	if (os) {
		delete os;
	}
}

void Streamer::stream(cv::Mat& img) {
	if (!is_init)
		lazy_init(img);

	spdlog::debug("Writing Image bytes {0}", img.dataend - img.datastart);
//	for (size_t i = 0; i < img.dataend - img.datastart; i++) {
//		spdlog::debug("{0}", i);
//		putchar(p_fd1[1],img.data[i]);
//	}
	auto res = write(p_fd1[1], img.data, img.dataend - img.datastart);
	spdlog::debug("Done Writing Image {0}", res);
	if (res < 0)
		perror("Writing image");

}

void Streamer::lazy_init(cv::Mat& img) {
	spdlog::debug("Lazy Init");
	if (is_init)
		return;

	auto args = fmt::format(o_args, img.cols, img.rows,
			"rtp://127.0.0.1:41954");


//	spdlog::debug("Size String {0}", size);
	if (0 < pipe(p_fd1)) {
		spdlog::error("pipe failed");
		perror("pipe failed");
	}

//	__gnu_cxx ::stdio_filebuf<char> filebuf(p_fd1[1], std::ios::out); // 1
//
//	os = new std::ostream(&filebuf);

	is_init = true;

	auto child_pid = fork();
	if (child_pid == 0) {
		std::vector<char *> v_argv;

		close(p_fd1[1]);
		close (STDOUT_FILENO);
		auto rv = dup2(p_fd1[0], STDIN_FILENO);
		if (rv < 0) {
			spdlog::error("dup2 failed");
			perror("dup2 failed");
		}
		spdlog::debug("Exec v");
		std::istringstream iss(args);
		std::string s;

		while (iss >> std::quoted(s)) {
			v_argv.push_back(strdup(s.c_str()));
			std::cout << s << std::endl;
		}
		v_argv.push_back(nullptr);

		auto result = execve(cmd.c_str(), &v_argv[0], nullptr);
		spdlog::error("Execv failed");
		perror("Exec failed");
		exit(0);

	} else {
		spdlog::debug("Other stream");
		close(p_fd1[0]);
	}
}

