#pragma once

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include <Qt>
#include <QMainWindow>
#include <QObject>
#include <QCompleter>
#include <QKeyEvent>
#include <QTabWidget>
#include <QFileInfo>
#include <QtWidgets>
#include <QMenu>
#include <QKeyEvent>
#include <QList>

#include "CodeEditor.h"
#include "TokenizerController.h"
#include "Compiler.h"
#include "VirtualMachine.h"
#include "Highlighter.h"
#include "OutputWindow.h"
#include "ExceptionWindow.h"
#include "Themer.h"

class CodeEditor;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    void SaveThemeSettings();
    void SetTheme(std::map<std::string, QColor> mainStyles);
    void SetOutputThemes(std::map<std::string, QString> outputColors);
    int GetCurrentTabPosition();
    void RemoveTab(int index);
    void AddNewTab();
    void addOutput(std::string output);
    void addException(std::string exception);
    void clearExceptions();
    void clearOutput();
    void AddFile(QFileInfo* info, QString text);
    void SetTabTitle(QFileInfo* info);
	void CodeIsExecuting(bool status);
	void PrintOutput();
    QString GetText();
    QAction* GetRunAction();
    QAction* GetClearAction();
    QAction* GetNewAction();
    QAction* GetLoadAction();
    QAction* GetSaveAction();
    QAction* GetSaveAsAction();
    QAction* GetQuitAction();
    QTabWidget* GetTabWidget();
    QString OpenLoadDialog();
    QString OpenSaveDialog();

private:
    int position;
    OutputWindow* outputWindow;
    ExceptionWindow* exceptionWindow;
    std::vector<CodeEditor*> codeEditorVector;
    Highlighter* highlighter;
    QCompleter* completer;
    QSplitter *splitter;
    QTabWidget* tabs;
    QTabWidget* outputTab;
    Themer themer;

    QAbstractItemModel *modelFromFile(const QString& fileName);
    CodeEditor* CreateEditor();

    // Theme 
    void CreateThemeMenu();

    // Menu include all menu items
    QMenuBar *menu;

    QMenu *fileMenu,
		  *viewMenu,
          *themeMenu,
          *macDebugMenu;

    QAction *runAction, 
            *clearAction, 
            *newAction, 
            *openAction, 
            *saveAction,
            *saveAsAction, 
            *quitAction;

    void ShowMenuBar();

private slots:
    void ChangeTheme();
};
