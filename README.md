# CS 100 Programming Project
Winter 2020

Justin Gomez 		SID: 862035390

Alec Asatoorian 	SID: 862026505


## Introduction
This project is to create a CLI shell.

## Diagram
![](images/FlowChart.jpeg)

## Classes

* Base
  This class will contain basic functions that  parse, execute, and connect strings of commands as a list 

    class Base{
    	base nextCom;
    	base currCom;
    	virtual execute();
    	virtual connect();;
    	void toString();
    };

* Command
  This class will contain its own implementation of execute() and connecting

    class Command : public Base{
    	void execute();
    	void connect();;
    };

* Prompt, Flag
  This class will contain objects such as -a

    class Prompt : public Command{ };
    class Flag : public Command{ };

* Argument
    class Argument : public Base{
    	void hasFailed();
    };

* Executable
    class Executable : public Argument{
    	bool isFailed;
    };

* Connector
  Base connector class for generic pass or fail statuses

    class Connector : public Argument{
    	void nextStat();
    	void currStat();
    	void prevStat();
    };

* Semicolon
  Links previous and next commands like newline

    class Semicolin : public Connector{
    	void execute();
    	void connect();
    };

* OR
  Links previous and next commands as logical "or" operator

    class OR : public Connector{
    	void execute();
    	void connect();
    };

* AND
  Links previous and next commands as logical "and" operator

    class AND : public Connector{
    	void execute();
    	void connect();
    };


## Prototypes/Research

## Development and Testing Roadmap

