// File INI
// Copyright (c) 2020-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2020-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILEINI_VERSION_HPP
#define XYO_FILEINI_VERSION_HPP

#ifndef XYO_FILEINI_DEPENDENCY_HPP
#	include <XYO/FileINI/Dependency.hpp>
#endif

namespace XYO::FileINI::Version {

	XYO_FILEINI_EXPORT const char *version();
	XYO_FILEINI_EXPORT const char *build();
	XYO_FILEINI_EXPORT const char *versionWithBuild();
	XYO_FILEINI_EXPORT const char *datetime();

};

#endif
