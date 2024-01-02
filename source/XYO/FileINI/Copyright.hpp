// File INI
// Copyright (c) 2020-2024 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2020-2024 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILEINI_COPYRIGHT_HPP
#define XYO_FILEINI_COPYRIGHT_HPP

#ifndef XYO_FILEINI_DEPENDENCY_HPP
#	include <XYO/FileINI/Dependency.hpp>
#endif

namespace XYO::FileINI::Copyright {
	XYO_FILEINI_EXPORT const char *copyright();
	XYO_FILEINI_EXPORT const char *publisher();
	XYO_FILEINI_EXPORT const char *company();
	XYO_FILEINI_EXPORT const char *contact();
};

#endif
