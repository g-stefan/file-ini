// File INI
// Copyright (c) 2020-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2020-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILEINI_DEPENDENCY_HPP
#define XYO_FILEINI_DEPENDENCY_HPP

#ifndef XYO_SYSTEM_HPP
#	include <XYO/System.hpp>
#endif

// -- Export

#ifndef XYO_FILEINI_INTERNAL
#	ifdef FILE_INI_INTERNAL
#		define XYO_FILEINI_INTERNAL
#	endif
#endif

#ifdef XYO_FILEINI_INTERNAL
#	define XYO_FILEINI_EXPORT XYO_LIBRARY_EXPORT
#else
#	define XYO_FILEINI_EXPORT XYO_LIBRARY_IMPORT
#endif

// --

namespace XYO::FileINI {
	using namespace XYO::ManagedMemory;
	using namespace XYO::DataStructures;
	using namespace XYO::Encoding;
	using namespace XYO::System;
};

#endif
