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

#ifndef TULIP_PLUGIN_H
#define TULIP_PLUGIN_H

#include <string>

#include <tulip/WithParameter.h>
#include <tulip/WithDependency.h>
#include <tulip/PluginContext.h>
#include <tulip/TulipRelease.h>

#ifdef major
#undef major
#endif

#ifdef minor
#undef minor
#endif

namespace tlp {

/**
 * @ingroup Plugins
 * @brief Splits the string and returns everything befor the first dot ('.').
 * This is used to return major version number, as version numbers are formatted as X.Y.Z,
 * X being the major, Y the minor, and Z the patch version.
 *
 * @return string The part of the string before the first dot.
 */
TLP_SCOPE std::string getMajor(const std::string &release);

/**
 * @ingroup Plugins
 * @brief Splits the string and return the minor version.
 * If the string does not contain any dot, then 0 is returned.
 * If the string contains only one dot (X.Y), then everything after the first dot is returned (Y).
 * If the string is a full version with two dots (X.Y.Z), everything between the first and last dots
 * is returned (Y).
 * If there are more than two dots, everything between the first and last dots is returned.
 */
TLP_SCOPE std::string getMinor(const std::string &release);

/**
 * @ingroup Plugins
 * @brief Top-level interface for plug-ins.
 *
 * This class holds meta-information about a plug-in (group/author/version...). It stands as a
 * unique base-class for every plugin type.
 * This interface is not intended to be directly sublassed. Plugin objects are mainly used
 * internally into the plugin lister system.
 *
 * This classe also holds extra information about the Tulip system such as the library version the
 * plugin was built against.
 * Plugin creation is handled by factories generated by the PLUGIN macro and the default Plugin
 * constructor should never be called as is.
 *
 * @see tlp::FactoryInterface for more advanced operation such as plugin creation and retrieving
 * dependencies.
 * @see tlp::PluginContext and its subclasses for parameters handling.
 *
 * @see tlp::Algorithm for plugins operating on the tlp::Graph structure.
 * @see tlp::TemplateAlgorithm and its subclasses for plugins operating on graph properties
 * @see tlp::View for panel plugins
 * @see tlp::Interactor for plugins responisble for user interactions.
 * @see tlp::Perspective for plugins handling the main GUI
 */
class TLP_SCOPE Plugin : public tlp::WithParameter, public tlp::WithDependency {
public:
  virtual ~Plugin() {}

  /**
    @brief The icon (preferably a thumbnail) of the plugin
    @return std::string the icon path
    */
  virtual std::string icon() const;

  /**
    @brief A string identifier for a plugin used for categorization purposes.
    @returns std::string the category of the plugin.
    */
  virtual std::string category() const = 0;

  /**
   * @brief Returns the name of the plug-in, as registered in the Tulip plug-in system.
   * This name must be unique, and if multiple plug-ins have the same name,
   * only the latest encountered will be considered.
   * @return string the name of the plug-in.
   */
  virtual std::string name() const = 0;

  /**
   * @brief Returns the name of the group this plug-in belongs to.
   * Groups and sub-groups are separated by two colons.
   * e.g. trees::planar trees
   * @return the group name of this plug-in.
   */
  virtual std::string group() const = 0;

  /**
   * @brief The name of the author of this plug-in.
   * @return the name of the author.
   */
  virtual std::string author() const = 0;

  /**
   * @brief The creation date of the plug-in.
   * This date is in a free format, but most Tulip plug-ins use a DD/MM/YYYY
   * @return the creation date.
   */
  virtual std::string date() const = 0;

  /**
   * @brief Information about the plug-in, from the plug-in author.
   * This information can contains anything, and the developer is completely free to put anything
   * here.
   * Most plug-ins by the Tulip team use an html format to generate help from these information.
   * @return string The information associated with this plug-in.
   */
  virtual std::string info() const = 0;

  /**
   * @brief The release version of the plug-in, including major and minor.
   * The version should be X.Y, X being the major, and Y the minor.
   * @return string The release version.
   */
  virtual std::string release() const = 0;

  /**
   * @brief The version of Tulip this plug-in was built with.
   * Tulip versions are X.Y.Z, X being the major, Y the minor, and Z the patch.
   *
   * @return The Tulip version the plug-in was built with.
   */
  virtual std::string tulipRelease() const = 0;

  /**
   * @brief Only the major of the plug-in version.
   * A version should be X.Y, X being the major.
   *
   * @return The major part of the plug-in version.
   */
  virtual std::string major() const;

  /**
   * @brief Only the minor of the plug-in version.
   * A version should be X.Y, Y being the major.
   *
   * @return The minor part of the plug-in version.
   */
  virtual std::string minor() const;

  /**
   * @return The major Tulip version the plug-in was built with.
   */
  virtual std::string tulipMajor() const;

  /**
   * @return Return the minor Tulip version this plug-in was built with.
   */
  virtual std::string tulipMinor() const;

  /**
  * @brief Returns the ID of the glyph this factory builds.
  * @TODO this member should be removed once there is a system in Tulip to handle glyphs.
  *
  * @return int the id of the glyph.
  **/
  virtual int id() const;

  virtual std::string programmingLanguage() const;
};

/**
 * @ingroup Plugins
 * @def PLUGININFORMATION(NAME, AUTHOR, DATE, INFO, RELEASE, GROUP)
 * @brief Declare meta-information for a plugin
 * This is an helper macro that defines every function related to a plugin meta-information (Plugin
 * name, author, etc).
 * When creating a new plugin, this macro avoids having to define pure-virtual methods located into
 * the Plugin interface and put them on the same line.
 * @note PLUGINIFORMATION should be declared into the Plugin's class body into the public scope
 *
 * @param NAME The plugin name as it will be registered into the plugins system
 * (tlp::Plugin::name())
 * @param AUTHOR The author of the plugin (tlp::Plugin::author())
 * @param DATE The creation date (tlp::Plugin::date())
 * @param INFO The plugin's description (tlp::Plugin::info())
 * @param RELEASE The plugin's version number (tlp::Plugin::version())
 * @param GROUP The plugin's group (tlp::Plugin::group()). If the plugin does not belong to any
 * group, set GROUP to "".
 *
 * @see tlp::Plugin
 * @see PLUGIN
 */
#define PLUGININFORMATION(NAME, AUTHOR, DATE, INFO, RELEASE, GROUP)                                \
  std::string name() const {                                                                       \
    return NAME;                                                                                   \
  }                                                                                                \
  std::string author() const {                                                                     \
    return AUTHOR;                                                                                 \
  }                                                                                                \
  std::string date() const {                                                                       \
    return DATE;                                                                                   \
  }                                                                                                \
  std::string info() const {                                                                       \
    return INFO;                                                                                   \
  }                                                                                                \
  std::string release() const {                                                                    \
    return RELEASE;                                                                                \
  }                                                                                                \
  std::string tulipRelease() const {                                                               \
    return TULIP_VERSION;                                                                          \
  }                                                                                                \
  std::string group() const {                                                                      \
    return GROUP;                                                                                  \
  }
}

// This include is here because the PluginLister needs to know the Plugin type, and the PLUGIN macro
// needs to know the PluginLister.
#include <tulip/PluginLister.h>
namespace tlp {
/**
 * @ingroup Plugins
 * @def PLUGIN(C)
 * @brief Register a plugin into the plugin system.
 * This macro is mandatory in order to register a plugin into Tulip. This will generate a Factory
that will handle the plugin's creation.
 * @param C The classname of the plugin.
 * @note This macro should be called outside of the class body @endnote
 *
@code{.cpp}
// This sample shows a basic skeleton for a plugin class declaration:
class MyPlugin: public tlp::PluginBase { // tlp::PluginBase is replaced by the actual Plugin
interface (tlp::Algorithm, tlp::View, etc)
  public:
  PLUGININFORMATION("My plugin", "Me", "28/09/2012", "My first plugin example", "1.0", "")
  // Class declaration and extra methods
};

PLUGIN(MyPlugin) // Register MyPlugin into Tulip
@endcode
 *
 * @see tlp::Plugin
 * @see PLUGININFORMATION
 */
#define PLUGIN(C)                                                                                  \
  class C##Factory : public tlp::FactoryInterface {                                                \
  public:                                                                                          \
    C##Factory() {                                                                                 \
      tlp::PluginLister::registerPlugin(this);                                                     \
    }                                                                                              \
    ~C##Factory() {}                                                                               \
    tlp::Plugin *createPluginObject(tlp::PluginContext *context) {                                 \
      C *tmp = new C(context);                                                                     \
      return tmp;                                                                                  \
    }                                                                                              \
  };                                                                                               \
                                                                                                   \
  extern "C" {                                                                                     \
  C##Factory C##FactoryInitializer;                                                                \
  }
}

#endif // TULIP_PLUGIN_H
