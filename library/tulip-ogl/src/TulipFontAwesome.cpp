/*
 *
 * This file is part of Tulip (http://tulip.labri.fr)
 *
 * Authors: David Auber and the Tulip development Team
 * from LaBRI, University of Bordeaux
 *
 * Tulip is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * Tulip is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 */

#include <cassert>
#include <cstring>
#include <FTLibrary.h>

#include <tulip/TulipFontAwesome.h>
#include <tulip/TlpTools.h>

#include <utf8.h>

#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

namespace tlp {

static map<std::string, vector<unsigned int>> iconCodePoint;
static unordered_map<std::string, const char *> iconFile;
static vector<std::string> iconsNames;
static map<std::string, FT_Face *> ftFaces;

static void clearFtFaces() {
  for (auto it = ftFaces.begin(); it != ftFaces.end(); ++it) {
    FT_Done_Face(*it->second);
    delete it->second;
  }
  ftFaces.clear();
}

static bool codePointExists(const std::string &fontFile, unsigned int codePoint) {
  const FT_Library *library = FTLibrary::Instance().GetLibrary();
  FT_Face *face;

  auto it = ftFaces.find(fontFile);
  if (it == ftFaces.end()) {
    std::string ttfFile(std::string(tlp::TulipBitmapDir).append(fontFile));
    face = new FT_Face();

    FT_Error err = FT_New_Face(*library, ttfFile.c_str(), 0, face);
    if (err) {
      delete face;
      return false;
    }

    err = FT_Select_Charmap(*face, FT_ENCODING_UNICODE);

    if (err) {
      delete face;
      return false;
    }
    ftFaces[fontFile] = face;
  } else
    face = it->second;

  return FT_Get_Char_Index(*face, codePoint) != 0;
}

static void addIconCodePoint(const string &iconName, unsigned int codePoint) {
  // we must find the ttf files for which the icon is defined
  bool iconFound = false;
  bool iconRegistered = false;
  if (codePointExists("fa-solid-900.ttf", codePoint)) {
    string name(iconName);
    if (iconName.find("-o", iconName.size() - 2) != std::string::npos)
      name.resize(iconName.size() - 2);
    else
      iconFound = true;
    iconCodePoint[name].push_back(codePoint);
    iconFile[name] = "fa-solid-900";
    iconRegistered = true;
  }
  // Warning !!!
  // because of a bug in QtAwesome which does not allow to manage font style
  // the fa-regular-400.ttf file embedded in Tulip
  // gives a different family name (Font Awesome 5 outl)
  // that the one downloaded from fontawesome.com
  // which have the same family name (Font Awesome 5 Free) that fa-solid-900.ttf
  if (codePointExists("fa-regular-400.ttf", codePoint)) {
    string name(iconName);
    if (iconFound)
      name.append("-o");
    iconCodePoint[name].push_back(codePoint);
    iconFile[name] = "fa-regular-400";
    iconFound = iconRegistered = true;
  }
  if (codePointExists("fa-brands-400.ttf", codePoint)) {
    string name(iconName);
    if (iconFound)
      name.append("-brand");
    iconCodePoint[name].push_back(codePoint);
    iconFile[name] = "fa-brands-400";
    iconRegistered = true;
  }
  assert(iconRegistered);
}

// code generated by generate_fa_init_cpp_code.sh
#include "TulipInitFontAwesome.cpp"

std::string TulipFontAwesome::getTTFLocation(const std::string &iconName) {
  if (iconCodePoint.empty())
    initIconCodePoints();
  return string(tlp::TulipBitmapDir).append(iconFile[iconName.c_str()]).append(".ttf");
}

std::string TulipFontAwesome::getWOFFLocation(const std::string &iconName) {
  if (iconCodePoint.empty())
    initIconCodePoints();
  return string(tlp::TulipBitmapDir).append(iconFile[iconName.c_str()]).append(".woff");
}

std::string TulipFontAwesome::getWOFF2Location(const std::string &iconName) {
  if (iconCodePoint.empty())
    initIconCodePoints();
  return string(tlp::TulipBitmapDir).append(iconFile[iconName.c_str()]).append(".woff2");
}

bool TulipFontAwesome::isIconSupported(const std::string &iconName) {
  if (iconCodePoint.empty()) {
    initIconCodePoints();
  }

  return iconCodePoint.find(iconName.c_str()) != iconCodePoint.end();
}

const vector<std::string> &TulipFontAwesome::getSupportedIcons() {
  if (iconCodePoint.empty()) {
    initIconCodePoints();
  }

  return iconsNames;
}

unsigned int TulipFontAwesome::getIconCodePoint(const std::string &iconName) {
  if (iconCodePoint.empty()) {
    initIconCodePoints();
  }

  auto it = iconCodePoint.find(iconName.c_str());

  if (it != iconCodePoint.end())
    return (it->second[0]);

  return 0;
}

std::string TulipFontAwesome::getIconFamily(const std::string &iconName) {
  if (iconCodePoint.empty()) {
    initIconCodePoints();
  }

  return iconFile[iconName.c_str()];
}

std::string TulipFontAwesome::getIconUtf8String(const std::string &iconName) {
  if (iconCodePoint.empty()) {
    initIconCodePoints();
  }

  std::string iconString;
  utf8::utf32to8(iconCodePoint[iconName.c_str()].begin(), iconCodePoint[iconName.c_str()].end(),
                 back_inserter(iconString));
  return iconString;
}
} // namespace tlp
