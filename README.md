# CS 100 Programming Project
Winter 2020

Justin Gomez 		SID: 862035390

Alec Asatoorian 	SID: 862026505


## Introduction
This project is to create a CLI shell.

## Diagram

![](images/FlowChart.jpeg)

## Classes
    class Base{
    	base nextCom;
        base currCom;
    	virtual execute();
        virtual connect();;
        void toString();
    };


    class Command : public Base{
    	void execute();
        void connect();;
    };
    class Prompt : public Command{ };
    class Flag : public Command{ };


    class Argument : public Base{
    	void hasFailed();
    };

    class Executable : public Argument{
    	bool isFailed;
    };

    class Connector : public Argument{
    	void nextStat();
   	void currStat();
    	void prevStat();
    };
    class Semicolin : public Connector{
    	void execute();
    	void connect();
    };
    class OR : public Connector{
        void execute();
        void connect();
    };
    class AND : public Connector{
        void execute();
        void connect();
    };


## Prototypes/Research

## Development and Testing Roadmap
