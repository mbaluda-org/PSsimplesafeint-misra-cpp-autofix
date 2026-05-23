/*********************************************************************************
 * This file is part of CUTE.
 *
 * Copyright (c) 2013-2018 Peter Sommerlad, IFS
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *********************************************************************************/

#ifndef CUTE_XML_FILE_H_
#define CUTE_XML_FILE_H_

#include <array>
#include <cstddef>
#include <cstdio>
#include <fstream>

namespace cute {
struct xml_file_opener {
	static constexpr std::size_t filename_capacity = static_cast<std::size_t>(FILENAME_MAX);
	std::array<char, filename_capacity> filename{};
	std::ofstream out;
	xml_file_opener(int argc, char const *const* argv)
	:filename{}
	,out(make_filename(argc, argv)){}
	char const *make_filename(int argc, char const *const* argv){
		if ((argc > 0) && (argv != nullptr) && (argv[0] != nullptr)) {
			return basename(argv[0]);
		}
		return basename("testresult");
	}
	char const *basename(char const *path){
		static constexpr char xml_suffix[] = ".xml";
		static constexpr std::size_t xml_suffix_length = sizeof(xml_suffix) - 1u;
#if defined( _MSC_VER ) || defined(__MINGW32__)
		char const sep='\\';
#else
		char const sep='/';
#endif
		filename.fill('\0');
		char const *base = path;
		for (char const *it = path; *it != '\0'; ++it){
			if (*it == sep) {
				base = it + 1;
			}
		}
		std::size_t index = 0u;
		while ((base[index] != '\0') && ((index + xml_suffix_length + 1u) < filename.size())) {
			filename[index] = base[index];
			++index;
		}
		for (std::size_t suffix_index = 0u; suffix_index < xml_suffix_length; ++suffix_index, ++index){
			filename[index] = xml_suffix[suffix_index];
		}
		filename[index] = '\0';
		return filename.data();
	}
};
}

#endif /* CUTE_XML_FILE_H_ */
