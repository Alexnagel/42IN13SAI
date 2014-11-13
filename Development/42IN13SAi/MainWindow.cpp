#include <QtWidgets>
#include <QMenu>

#include "MainWindow.h"
#include "CodeEditor.h"
#include "TokenizerController.h"
#include "Compiler.h"
#include "VirtualMachine.h"

MainWindow::MainWindow(QWidget *parent)
{
	showMenuBar();
	codeEditor = new CodeEditor();
	highlighter = new Highlighter(codeEditor->document());

	this->setCentralWidget(codeEditor);
}

void MainWindow::showMenuBar()
{
	// Create menu bar
	QMenuBar* menu = nullptr;

	#ifdef _WIN32
		menu = new QMenuBar();
	#else
        // Mac OS X needs menubar without a parent
		menu = new QMenuBar(0);
    
        // Also needs a menu to show the items, doesn't work with only actions
		QMenu* mainMenu = menu->addMenu("File");
	#endif

	// Create action and connect
	runAction = menu->addAction("Run");
	clearAction = menu->addAction("Clear console");

	#ifndef _WIN32
        // Add the actions to the menu
		mainMenu->addAction(runAction);
		mainMenu->addAction(clearAction);
	#endif

	// Set the menu bar on ui from left to right
	this->setMenuBar(menu);
	menu->setLayoutDirection(Qt::LeftToRight);
}

QAction *MainWindow::getRunAction()
{
	return runAction;
}

QAction *MainWindow::getClearAction()
{
	return clearAction;
}

QString MainWindow::getText()
{
	return codeEditor->toPlainText();
}

MainWindow::~MainWindow()
{
	// Empty
}