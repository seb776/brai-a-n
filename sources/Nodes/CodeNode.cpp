/*
** Author: Sebastien Maire
** Contribs:
*/

#include "CodeNode.hpp"
#include "OnTheFly\CompilerAttr.hpp"
#include "OnTheFly\NodeMainAttr.hpp"

using namespace System;
using namespace OnTheFly;

CodeNode::CodeNode(String ^code) :
	ANode(), code_(code), res_(nullptr), rebuild_(true), language_(LanguageSel::CSHARP) {
}

void CodeNode::Build() {
	TextWriter ^errorWriter = Console::Error;
	CompilerResults ^newRes = nullptr;

	newRes = CompilerAttr::provider[(int)language_]->CompileAssemblyFromSource(CompilerAttr::compilerParams, code_);
	if (newRes->Errors->Count != 0) {
		errorWriter->WriteLine("ERROR: [0x04]: Cannot build due to source build fail on node \"{0}\".", name_);
		for each (CompilerError ^ce in newRes->Errors) {
			errorWriter->WriteLine(ce);
		}
		return ;
	}
	array<Type ^>	^types = newRes->CompiledAssembly->GetTypes();
	Type ^entryClass = nullptr;
	for each (Type ^t in types) {
		if (entryClass && t->GetCustomAttributes(MainEntry::typeid, false)->Length > 0) {
			errorWriter->WriteLine("ERROR: [0x02]: Cannot build because there are too many EntryClass.");
			return ;
		}
		if (t->GetCustomAttributes(MainEntry::typeid, false)->Length > 0) {
			entryClass = t;
		}
	}
	if (!entryClass) {
		errorWriter->WriteLine("ERROR: [0x00]: Cannot build because there�s no EntryClass. (Must set [MainEntry] on a class.)");
		return ;
	}
	instance_ = newRes->CompiledAssembly->CreateInstance(entryClass->FullName);
	entryPoint_ = nullptr;
	for each (MethodInfo ^i in entryClass->GetMethods()) {
		if (entryPoint_ && i->GetCustomAttributes(MainEntry::typeid, false)->Length > 0) {
			errorWriter->WriteLine("ERROR: [0x03]: Cannot build because there are too many EntryMethod in node \"{0}\".", name_);
			return ;
		}
		if (i->GetCustomAttributes(MainEntry::typeid, false)->Length > 0) {
			entryPoint_ = i;
		}
	}
	if (!entryPoint_) {
		errorWriter->WriteLine("ERROR: [0x01]: Cannot build because there�s no EntryMethod. (Must set [MainEntry] on a method of the class tagged [MainEntry]\"{0}\".)", name_);
		return ;
	}
	res_ = newRes;
}

generic<typename T>
void CodeNode::Process(T value) {
	if (rebuild_) {
		this->Build();
		rebuild_ = false;
	}
	if (res_) {
		//Console::WriteLine(name_);

		entryPoint_->Invoke(instance_, gcnew array < Object ^ > {childs_, value});
	}
}