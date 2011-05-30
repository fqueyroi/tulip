/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c TulipAgentServiceAdaptor -a include/TulipAgentServiceAdaptor.h:src/TulipAgentServiceAdaptor.cpp resources/org.labri.TulipAgentService.xml
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef TULIPAGENTSERVICEADAPTOR_H_1306752155
#define TULIPAGENTSERVICEADAPTOR_H_1306752155

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;

/*
 * Adaptor class for interface org.labri.Tulip
 */
class TulipAgentServiceAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.labri.Tulip")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.labri.Tulip\">\n"
"    <property access=\"read\" type=\"s\" name=\"pid\"/>\n"
"    <method name=\"ShowWelcomeScreen\"/>\n"
"    <method name=\"ShowPluginsCenter\"/>\n"
"    <method name=\"ShowAboutPage\"/>\n"
"  </interface>\n"
        "")
public:
    TulipAgentServiceAdaptor(QObject *parent);
    virtual ~TulipAgentServiceAdaptor();

public: // PROPERTIES
    Q_PROPERTY(QString pid READ pid)
    QString pid() const;

public Q_SLOTS: // METHODS
    void ShowAboutPage();
    void ShowPluginsCenter();
    void ShowWelcomeScreen();
Q_SIGNALS: // SIGNALS
};

#endif
