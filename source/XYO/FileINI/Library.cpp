// File INI
// Copyright (c) 2020-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2020-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/FileINI/Library.hpp>

namespace XYO::FileINI {

	bool load(const char *fileName, Document &document) {
		File file;
		String line;
		String lineX;
		String trimElements = " \t\r\n";
		document.empty();
		size_t index = 0;
		size_t indexValue;
		if (file.openRead(fileName)) {
			while (Stream::readLn(file, line, 32768)) {
				Line &iniLine = document[index];
				lineX = line.trimWithElement(trimElements);
				if (lineX.isEmpty()) {
					iniLine.type = LineType::None;
					++index;
					continue;
				};
				if (lineX[0] == ';') {
					iniLine.type = LineType::Comment;
					iniLine.value = lineX;
					++index;
					continue;
				};
				if (lineX[0] == '[') {
					iniLine.type = LineType::Section;
					iniLine.value = lineX;
					++index;
					continue;
				};
				if (lineX.indexOf("=", 0, indexValue)) {
					iniLine.type = LineType::Value;
					iniLine.key = lineX.substring(0, indexValue);
					iniLine.value = lineX.substring(indexValue + 1);
					++index;
					continue;
				};
				iniLine.type = LineType::None;
				iniLine.value = lineX;
				++index;
			};
			file.close();
			return true;
		};
		return false;
	};

	bool save(const char *fileName, Document &document) {
		File file;
		if (file.openWrite(fileName)) {
			size_t k;
			for (k = 0; k < document.length(); ++k) {
				switch (document[k].type) {
				case LineType::Comment:
					Stream::write(file, document[k].value);
					Stream::write(file, "\r\n");
					break;
				case LineType::Section:
					Stream::write(file, document[k].value);
					Stream::write(file, "\r\n");
					break;
				case LineType::Value:
					Stream::write(file, document[k].key);
					Stream::write(file, "=");
					Stream::write(file, document[k].value);
					Stream::write(file, "\r\n");
					break;
				default:
					if (document[k].value.length() > 0) {
						Stream::write(file, document[k].value);
					};
					Stream::write(file, "\r\n");
					break;
				};
			};
			file.close();
			return true;
		};
		return false;
	};

	bool hasSection(Document &document, const char *section) {
		size_t k;
		String sectionX;
		sectionX << "[" << section << "]";
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				if (document[k].value == sectionX) {
					return true;
				};
			};
		};
		return false;
	};

	size_t count(Document &document, const char *section, const char *key) {
		size_t count = 0;
		size_t k;
		String sectionX;
		bool inSection = false;
		sectionX << "[" << section << "]";
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				if (inSection) {
					return count;
				};
				if (document[k].value == sectionX) {
					inSection = true;
				};
				continue;
			};
			if ((document[k].type == LineType::Value) && inSection) {
				if (document[k].key == key) {
					++count;
				};
			};
		};
		return count;
	};

	bool get(Document &document, const char *section, const char *key, String &value, size_t index) {
		size_t k;
		String sectionX;
		bool inSection = false;
		sectionX << "[" << section << "]";
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				if (inSection) {
					return false;
				};
				if (document[k].value == sectionX) {
					inSection = true;
				};
				continue;
			};
			if ((document[k].type == LineType::Value) && inSection) {
				if (document[k].key == key) {
					if (index == 0) {
						value = document[k].value;
						return true;
					};
					--index;
				};
			};
		};
		return false;
	};

	bool set(Document &document, const char *section, const char *key, const char *value, size_t index) {
		size_t k;
		String sectionX;
		bool inSection = false;
		sectionX << "[" << section << "]";
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				if (inSection) {
					int lastK = k - 1;
					for (; k > 0; --k) {
						if (document[k].type == LineType::Value) {
							lastK = k + 1;
						};
					};
					Line &line = document.insert(lastK);
					line.type = LineType::Value;
					line.key = key;
					line.value = value;
					return true;
				};
				if (document[k].value == sectionX) {
					inSection = true;
				};
				continue;
			};
			if (inSection) {
				if (document[k].type == LineType::Value) {
					if (document[k].key == key) {
						if (index == 0) {
							document[k].value = value;
							return true;
						};
						--index;
					};
				};
			};
		};
		if (inSection == false) {
			document[k].type = LineType::Section;
			document[k].value = sectionX;
			++k;
		};
		while (index > 0) {
			document[k].type = LineType::Value;
			document[k].key = key;
			document[k].value = "";
			++k;
			--index;
		};
		document[k].type = LineType::Value;
		document[k].key = key;
		document[k].value = value;
		return true;
	};

	bool removeKey(Document &document, const char *section, const char *key, size_t index) {
		size_t k;
		String sectionX;
		bool inSection = false;
		sectionX << "[" << section << "]";
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				if (inSection) {
					return false;
				};
				if (document[k].value == sectionX) {
					inSection = true;
				};
				continue;
			};
			if ((document[k].type == LineType::Value) && inSection) {
				if (document[k].key == key) {
					if (index > 0) {
						--index;
						continue;
					};
					document.remove(k);
					return true;
				};
			};
		};
		return false;
	};

	bool addSection(Document &document, const char *section) {
		size_t k;
		String sectionX;
		sectionX << "[" << section << "]";
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				if (document[k].value == sectionX) {
					return true;
				};
			};
		};
		document[k].type = LineType::Section;
		document[k].value = sectionX;
		return true;
	};

	bool removeSection(Document &document, const char *section) {
		size_t k;
		String sectionX;
		sectionX << "[" << section << "]";
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				if (document[k].value == sectionX) {
					size_t endK = k;
					for (; endK < document.length(); ++endK) {
						if (document[endK].type == LineType::Section) {
							break;
						};
					};
					size_t index = k;
					for (; k < endK; ++k) {
						document.remove(index);
					};
					return true;
				};
			};
		};
		return true;
	};

	bool sectionIndex(Document &document, const char *section, size_t &index) {
		size_t k;
		String sectionX;
		sectionX << "[" << section << "]";
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				if (document[k].value == sectionX) {
					index = k;
					return true;
				};
			};
		};
		return false;
	};

	bool sectionLastIndex(Document &document, const char *section, size_t &index) {
		size_t k;
		String sectionX;
		sectionX << "[" << section << "]";
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				if (document[k].value == sectionX) {
					for (++k; k < document.length(); ++k) {
						if (document[k].type == LineType::Section) {
							--k;
							break;
						};
					};
					index = k;
					return true;
				};
			};
		};
		return false;
	};

	bool joinSection(Document &document, const char *section, Document &iniSource, const char *sectionSource) {
		size_t indexSource;
		if (sectionIndex(iniSource, sectionSource, indexSource)) {
			if (!hasSection(document, section)) {
				if (!addSection(document, section)) {
					return false;
				};
			};
			size_t indexDestination;
			if (sectionLastIndex(document, section, indexDestination)) {
				if (indexDestination < document.length()) {
					if (document[indexDestination].type == LineType::None) {
						--indexDestination;
					};
				};
				++indexSource;
				for (; indexSource < iniSource.length(); ++indexSource, ++indexDestination) {
					if (iniSource[indexSource].type == LineType::Section) {
						break;
					};
					Line &line = document.insert(indexDestination);
					line.type = iniSource[indexSource].type;
					line.key = iniSource[indexSource].key.value();
					line.value = iniSource[indexSource].value.value();
				};
				return true;
			};
		};
		return false;
	};

	bool hasKeyWithValue(Document &document, const char *section, const char *key, const char *value) {
		size_t k;
		String sectionX;
		bool inSection = false;
		sectionX << "[" << section << "]";
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				if (inSection) {
					return false;
				};
				if (document[k].value == sectionX) {
					inSection = true;
				};
				continue;
			};
			if ((document[k].type == LineType::Value) && inSection) {
				if (document[k].key == key) {
					if (document[k].value == value) {
						return true;
					};
				};
			};
		};
		return false;
	};

	bool insert(Document &document, const char *section, const char *key, const char *value) {
		size_t k;
		String sectionX;
		bool inSection = false;
		sectionX << "[" << section << "]";
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				if (inSection) {
					int lastK = k - 1;
					for (; k > 0; --k) {
						if (document[k].type == LineType::Value) {
							lastK = k + 1;
						};
					};
					Line &line = document.insert(lastK);
					line.type = LineType::Value;
					line.key = key;
					line.value = value;
					return true;
				};
				if (document[k].value == sectionX) {
					inSection = true;
				};
				continue;
			};
		};
		if (inSection == false) {
			document[k].type = LineType::Section;
			document[k].value = sectionX;
			++k;
		};
		document[k].type = LineType::Value;
		document[k].key = key;
		document[k].value = value;
		return true;
	};

	bool getValues(Document &document, const char *section, const char *key, TDynamicArray<String> &values) {
		bool found = false;
		size_t k;
		String sectionX;
		bool inSection = false;
		sectionX << "[" << section << "]";
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				if (inSection) {
					return false;
				};
				if (document[k].value == sectionX) {
					inSection = true;
				};
				continue;
			};
			if ((document[k].type == LineType::Value) && inSection) {
				if (document[k].key == key) {
					values.push(document[k].value);
					found = true;
				};
			};
		};
		return found;
	};

	bool renameSection(Document &document, const char *sectionOld, const char *sectionNew) {
		size_t index;
		if (sectionIndex(document, sectionOld, index)) {
			String sectionX;
			sectionX << "[" << sectionNew << "]";
			document[index].value = sectionX;
			return true;
		};
		return false;
	};

	size_t countSection(Document &document) {
		size_t count = 0;
		size_t k;
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				++count;
			};
		};
		return count;
	};

	bool getSection(Document &document, size_t index, String &section) {
		size_t k;
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				if (index == 0) {
					section = document[index].value.substring(1, document[index].value.length() - 2);
					return true;
				};
				--index;
			};
		};
		return false;
	};

	bool getKeysAndValues(Document &document, const char *section, TRedBlackTree<String, String> &keyAndValues) {
		bool found = false;
		size_t k;
		String sectionX;
		bool inSection = false;
		sectionX << "[" << section << "]";
		for (k = 0; k < document.length(); ++k) {
			if (document[k].type == LineType::Section) {
				if (inSection) {
					return false;
				};
				if (document[k].value == sectionX) {
					inSection = true;
				};
				continue;
			};
			if ((document[k].type == LineType::Value) && inSection) {
				keyAndValues.set(document[k].key, document[k].value);
				found = true;
			};
		};
		return found;
	};

};
