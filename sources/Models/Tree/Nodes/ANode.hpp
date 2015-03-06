/*
** Author: Sebastien Maire
** Contribs:
*/

#pragma once

#using <System.dll>
#include "BrainView\include.h"


using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Controls;

ref class Counter {
public:
	static int last = 0;
	static LinkedList<int> ^avnames = gcnew LinkedList<int>();
	static int getNumber() {
		int num;
		if (avnames->Count > 0) {
			num = Counter::avnames->First->Value;
			avnames->RemoveFirst();
		}
		else
		{
			num = last++;
		}
		return num;
	}
	static void removeNumber(int n) {
		Counter::avnames->Remove(n);
	}
};

[SerializableAttribute]
public ref class ANode abstract {
protected:
	Dictionary<String^, ANode^>	^children_;
	UInt32	posX_;
	UInt32	posY_;
public:
	int number;
	String ^name_;
	ANode();
// Getters, setters
	void			setPosition(UInt32 x, UInt32 y);
	Tuple<UInt32, UInt32>			^getPosition();
	String	^getName();
	Dictionary<String ^, ANode ^>	^getChildren();

	bool AddChild(ANode ^node);
	void RemoveChild(String ^name);
	generic<typename T>
	virtual void Process(T val) abstract;
};
