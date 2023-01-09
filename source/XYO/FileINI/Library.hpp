// File INI
// Copyright (c) 2020-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2020-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_FILEINI_LIBRARY_HPP
#define XYO_FILEINI_LIBRARY_HPP

#ifndef XYO_FILEINI_DEPENDENCY_HPP
#	include <XYO/FileINI/Dependency.hpp>
#endif

namespace XYO::FileINI {

	enum struct LineType {
		None = 0,
		Comment = 1,
		Section = 2,
		Value = 3
	};

	struct Line : Object {
			LineType type;
			String key;
			String value;

			inline Line() {
				type = LineType::None;
			};

			inline Line(const Line &line) {
				type = line.type;
				key = line.key;
				value = line.value;
			};

			inline Line(Line &&line) {
				type = line.type;
				key = std::move(line.key);
				value = std::move(line.value);
			};

			inline Line &operator=(const Line &line) {
				type = line.type;
				key = line.key;
				value = line.value;
				return *this;
			};

			inline Line &operator=(Line &&line) {
				type = line.type;
				key = std::move(line.key);
				value = std::move(line.value);
				return *this;
			};

			inline ~Line(){};

			static inline void initMemory() {
				String::initMemory();
			};

			inline void activeDestructor() {
				type = LineType::None;
				key.activeDestructor();
				value.activeDestructor();
			};
	};

	typedef TDynamicArray<Line> Document;

	XYO_FILEINI_EXPORT bool load(const char *fileName, Document &document);
	XYO_FILEINI_EXPORT bool save(const char *fileName, Document &document);
	XYO_FILEINI_EXPORT bool hasSection(Document &document, const char *section);
	XYO_FILEINI_EXPORT size_t count(Document &document, const char *section, const char *key);
	XYO_FILEINI_EXPORT bool get(Document &document, const char *section, const char *key, String &value, size_t index = 0);
	XYO_FILEINI_EXPORT bool set(Document &document, const char *section, const char *key, const char *value, size_t index = 0);
	XYO_FILEINI_EXPORT bool removeKey(Document &document, const char *section, const char *key, size_t index = 0);
	XYO_FILEINI_EXPORT bool addSection(Document &document, const char *section);
	XYO_FILEINI_EXPORT bool removeSection(Document &document, const char *section);
	XYO_FILEINI_EXPORT bool sectionIndex(Document &document, const char *section, size_t &index);
	XYO_FILEINI_EXPORT bool sectionLastIndex(Document &document, const char *section, size_t &index);
	XYO_FILEINI_EXPORT bool joinSection(Document &document, const char *section, Document &iniSource, const char *sectionSource);
	XYO_FILEINI_EXPORT bool hasKeyWithValue(Document &document, const char *section, const char *key, const char *value);
	XYO_FILEINI_EXPORT bool insert(Document &document, const char *section, const char *key, const char *value);
	XYO_FILEINI_EXPORT bool getValues(Document &document, const char *section, const char *key, TDynamicArray<String> &values);
	XYO_FILEINI_EXPORT bool renameSection(Document &document, const char *sectionOld, const char *sectionNew);
	XYO_FILEINI_EXPORT size_t countSection(Document &document);
	XYO_FILEINI_EXPORT bool getSection(Document &document, size_t index, String &section);
	XYO_FILEINI_EXPORT bool getKeysAndValues(Document &document, const char *section, TRedBlackTree<String, String> &keyAndValues);

};

#endif
