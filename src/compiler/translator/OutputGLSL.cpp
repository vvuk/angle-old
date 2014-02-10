//
// Copyright (c) 2002-2011 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#include "compiler/translator/OutputGLSL.h"

TOutputGLSL::TOutputGLSL(TInfoSinkBase& objSink,
                         ShArrayIndexClampingStrategy clampingStrategy,
                         ShHashFunction64 hashFunction,
                         NameMap& nameMap,
                         TSymbolTable& symbolTable)
    : TOutputGLSLBase(objSink, clampingStrategy, hashFunction, nameMap, symbolTable)
{
}

bool TOutputGLSL::writeVariablePrecision(TPrecision)
{
    return false;
}

void TOutputGLSL::visitSymbol(TIntermSymbol* node)
{
    TInfoSinkBase& out = objSink();

    if (node->getSymbol() == "gl_FragDepthEXT")
    {
        out << "gl_FragDepth";
    }
    else
    {
        TOutputGLSLBase::visitSymbol(node);
    }
}

bool TOutputGLSL::overrideFunctionName(TString& name)
{
    static const char *simpleRename[] = {
        "texture2DLodEXT", "texture2DLod",
        "texture2DProjLodEXT", "texture2DProjLod",
        "textureCubeLodEXT", "textureCubeLod",
        "texture2DGradEXT", "texture2DGradARB",
        "texture2DProjGradEXT", "texture2DProjGradARB",
        "textureCubeGradEXT", "textureCubeGradARB",
        NULL, NULL
    };

    for (int i = 0; simpleRename[i] != NULL; ++i) {
        if (name == simpleRename[i]) {
            name = simpleRename[i+1];
            return true;
        }
    }

    return false;
}
