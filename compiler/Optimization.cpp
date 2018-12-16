//
// Created by JJJJJJJiyun on 2018/12/12.
//

#include "Optimization.h"
#include "Compiler.h"
#include "definition.h"

std::string ZEROSTR = std::string("0");

void Compiler::zeroAndDuplicateOptimize() {
    int index = this->midCodeIndex;
    this->midCodeIndex = 0;
    for (int i = 0; i < index; i++) {
        midCode *code = this->midCodes[i];
        std::string *op1 = code->op1;
        std::string *op2 = code->op2;
        std::string *res = code->res;
        switch (code->op) {
            case ADD: {
                if (!((this->isEqual(*op1, ZEROSTR) && this->isEqual(*op2, *res)) ||
                      (this->isEqual(*op2, ZEROSTR) && this->isEqual(*op2, *res)))) {
                    this->midCodes[this->midCodeIndex++] = code;
                }
            }
                break;
            case SUB: {
                if (!(this->isEqual(*op1, *res) && this->isEqual(*op2, ZEROSTR)))
                    this->midCodes[this->midCodeIndex++] = code;
            }
                break;
            case LABEL: {
                this->midCodes[this->midCodeIndex++] = code;
                for (int j = i + 1; j < index; j++) {
                    midCode *label = this->midCodes[j];
                    if (label->op != LABEL)
                        break;
                    else {
                        i++;
                        std::string *name = label->res;
                        for (int k = 0; k < index; k++) {
                            midCode *replace = this->midCodes[k];
                            if ((replace->op == GOTO || replace->op == EQU || replace->op == NEQU ||
                                 replace->op == LESS || replace->op == LESSEQU || replace->op == GRE ||
                                 replace->op == GREEQU) &&
                                this->isEqual(*replace->res, *name))
                                *replace->res = *res;
                        }
                    }
                }
            }
                break;
            case GOTO: {
                midCode *deleteCode = this->midCodes[i + 1];
                if (deleteCode->op == GOTO) {
                    this->midCodes[this->midCodeIndex++] = code;
                    i++;
                } else
                    this->midCodes[this->midCodeIndex++] = code;
            }
                break;
            default:
                this->midCodes[this->midCodeIndex++] = code;
        }
    }
    index = this->midCodeIndex;
    this->midCodeIndex = 0;
    for (int i = 0; i < index; i++) {
        midCode *code = this->midCodes[i];
        switch (code->op) {
            case GOTO: {
                midCode *next = this->midCodes[i + 1];
                if (next->op == LABEL && this->isEqual(*next->res, *code->res)) {
                    this->midCodes[this->midCodeIndex++] = next;
                    i++;
                } else
                    this->midCodes[this->midCodeIndex++] = code;
            }
                break;
            default:
                this->midCodes[this->midCodeIndex++] = code;
        }
    }
}

void Compiler::initBlock(int index) {
    Block *block = new Block;
    block->preNum = 0;
    block->next1 = -1;
    block->next2 = -1;
    this->blockArray[this->blockIndex] = block;
    this->blockBegin[this->blockIndex++] = index;
    this->blockBeginFlag[index] = true;
}

void Compiler::blockDivide() {
    int funcNum = 0;
    for (int i = 0; i < this->midCodeIndex; i++) {
        midCode *code = this->midCodes[i];
        switch (code->op) {
            case LABEL:
                if (!this->blockBeginFlag[i]) {
                    initBlock(i);
                }
                break;
            case EXIT:
            case CALL:
            case GOTO:
            case EQU:
            case NEQU:
            case LE:
            case LEEQU:
            case GRE:
            case GREEQU:
            case RET:
                if ((i + 1 < this->midCodeIndex) && !this->blockBeginFlag[i + 1]) {
                    initBlock(i+1);
                }
                break;
            case FUNC:
                this->funcBlockBegin[funcNum++] = this->blockBeginFlag[i] ? this->blockIndex - 1 : this->blockIndex;
                if (!this->blockBeginFlag[i]) {
                    initBlock(i);
                }
                if (!this->blockBeginFlag[i + 1]) {
                    initBlock(i+1);
                }
                break;
        }
    }
    this->outData = new bool *[this->blockIndex];
}

void Compiler::findLabel(std::string *label, int *index) {
    for (int i = 0; i < this->blockIndex; i++) {
        int begin = this->blockBegin[i];
        midCode *code = this->midCodes[begin];
        if (code->op == LABEL) {
            if (this->isEqual(*(code->res), *label)) {
                *index = i;
                break;
            }
        }
    }
}

void Compiler::connectBlock() {
    for (int i = 0; i < this->blockIndex; i++) {
        int end = i + 1 >= this->blockIndex ? this->midCodeIndex : this->blockBegin[i + 1];
        Block *pre = this->blockArray[i];
        int preIndex = i;
        midCode *code = this->midCodes[end - 1];
        switch (code->op) {
            case EQU:
            case NEQU:
            case LE:
            case LEEQU:
            case GRE:
            case GREEQU: {
                pre->next1 = preIndex + 1;
                Block *next = this->blockArray[preIndex + 1];
                next->preArray[next->preNum++] = preIndex;
                std::string *label = code->res;
                int branch = -1;
                this->findLabel(label, &branch);
                pre->next2 = branch;
                next = this->blockArray[branch];
                next->preArray[next->preNum++] = preIndex;
            }
                break;
            case GOTO: {
                std::string *label = code->res;
                int next = -1;
                this->findLabel(label, &next);
                pre->next2 = next;
                Block *nextBlock = this->blockArray[next];
                nextBlock->preArray[nextBlock->preNum++] = preIndex;
            }
                break;
            case EXIT:
                break;
            case RET:
                break;
            default: {
                pre->next1 = preIndex + 1;
                Block *next = this->blockArray[preIndex + 1];
                next->preArray[next->preNum++] = preIndex;
            }
        }
    }
}

void Compiler::outputBlock() {
    for (int i = 0; i < blockIndex; i++) {
        this->blockOutFile << "No." << i << std::endl;
        Block *block = this->blockArray[i];
        int begin = this->blockBegin[i];
        int end = i + 1 >= this->blockIndex ? this->midCodeIndex : this->blockBegin[i + 1];
        for (int j = begin; j < end; j++) {
            midCode *code = this->midCodes[j];
            this->blockOutFile << this->midMessage[code->op] << " " << *code->op1 << " " << *code->op2 << " "
                               << *code->res
                               << std::endl;
        }
        this->blockOutFile << "后继基本块：" << std::endl;
        if (block->next1 != -1)
            this->blockOutFile << block->next1 << " ";
        if (block->next2 != -1)
            this->blockOutFile << block->next2 << std::endl;
        this->blockOutFile << "前驱基本块：" << std::endl;
        for (int j = 0; j < block->preNum; j++) {
            this->blockOutFile << block->preArray[j] << " ";
        }
        this->blockOutFile << std::endl << std::endl;
    }
}

void Compiler::getIndex(int *index, int funcRef, std::string *name) {
    for (int i = 0; i < this->funcSymbolNum[funcRef]; i++) {
        symbol *sym = this->funcSymbolTab[funcRef][i];
        if (this->isEqual(*sym->name, *name)) {
            *index = i;
            return;
        }
    }
}

void Compiler::dataFlowAnalyze() {
    bool **use = new bool *[this->blockIndex];
    bool **def = new bool *[this->blockIndex];
    bool **in = new bool *[this->blockIndex];
    bool **out = new bool *[this->blockIndex];
    for (int i = 0; i < this->funcNum; i++) {
        int funcRef = i;
        int blockBegin = this->funcBlockBegin[i];
        int blockEnd = i + 1 >= funcNum ? this->blockIndex : this->funcBlockBegin[i + 1];
        int symNum = this->funcSymbolNum[funcRef];
        for (int j = blockEnd - 1; j >= blockBegin; j--) {
            use[j] = new bool[symNum];
            def[j] = new bool[symNum];
            in[j] = new bool[symNum];
            out[j] = new bool[symNum];
        }
        for (int j = blockEnd - 1; j >= blockBegin; j--) {
            int blockIndex = j;
            int begin = this->blockBegin[j];
            int end = j + 1 >= this->blockIndex ? this->midCodeIndex : this->blockBegin[j + 1];
            for (int k = 0; k < symNum; k++) {
                use[j][k] = false;
                def[j][k] = false;
                in[j][k] = false;
                out[j][k] = false;
            }
            for (int k = begin; k < end; k++) {
                midCode *code = this->midCodes[k];
                switch (code->op) {
                    case ADD:
                    case SUB:
                    case MUL:
                    case DIV: {
                        std::string *op1 = code->op1;
                        std::string *op2 = code->op2;
                        std::string *res = code->res;
                        if (this->isOperandId(op1) || this->isOperandTemp(op1)) {
                            int index = -1;
                            this->getIndex(&index, funcRef, op1);
                            if (index != -1 && !def[blockIndex][index])
                                use[blockIndex][index] = true;
                        }
                        if (this->isOperandId(op2) || this->isOperandTemp(op2)) {
                            int index = -1;
                            this->getIndex(&index, funcRef, op2);
                            if (index != -1 && !def[blockIndex][index])
                                use[blockIndex][index] = true;
                        }
                        if (this->isOperandId(res) || this->isOperandTemp(res)) {
                            int index = -1;
                            this->getIndex(&index, funcRef, res);
                            if (index != -1 && !use[blockIndex][index])
                                def[blockIndex][index] = true;
                        }
                    }
                        break;
                    case PARA: {
                        std::string *res = code->res;
                        if (this->isOperandId(res) || this->isOperandTemp(res)) {
                            int index = -1;
                            this->getIndex(&index, funcRef, res);
                            if (index != -1 && !def[blockIndex][index])
                                use[blockIndex][index] = true;
                        }
                    }
                        break;
                    case RARRAY: {
                        std::string *op2 = code->op2;
                        std::string *res = code->res;
                        if (this->isOperandId(op2) || this->isOperandTemp(op2)) {
                            int index = -1;
                            this->getIndex(&index, funcRef, op2);
                            if (index != -1 && !def[blockIndex][index])
                                use[blockIndex][index] = true;
                        }
                        if (this->isOperandId(res) || this->isOperandTemp(res)) {
                            int index = -1;
                            this->getIndex(&index, funcRef, res);
                            if (index != -1 && !use[blockIndex][index])
                                def[blockIndex][index] = true;
                        }
                    }
                        break;
                    case EQU:
                    case NEQU:
                    case LE:
                    case LEEQU:
                    case GRE:
                    case GREEQU: {
                        std::string *op1 = code->op1;
                        std::string *op2 = code->op2;
                        if (this->isOperandId(op1) || this->isOperandTemp(op1)) {
                            int index = -1;
                            this->getIndex(&index, funcRef, op1);
                            if (index != -1 && !def[blockIndex][index])
                                use[blockIndex][index] = true;
                        }
                        if (this->isOperandId(op2) || this->isOperandTemp(op2)) {
                            int index = -1;
                            this->getIndex(&index, funcRef, op2);
                            if (index != -1 && !def[blockIndex][index])
                                use[blockIndex][index] = true;
                        }
                    }
                        break;
                    case SCAN: {
                        std::string *res = code->res;
                        if (this->isOperandId(res) || this->isOperandTemp(res)) {
                            int index = -1;
                            this->getIndex(&index, funcRef, res);
                            if (index != -1 && !use[blockIndex][index])
                                def[blockIndex][index] = true;
                        }
                    }
                        break;
                    case PRINT: {
                        std::string *res = code->res;
                        if (this->isOperandId(res) || this->isOperandTemp(res)) {
                            int index = -1;
                            this->getIndex(&index, funcRef, res);
                            if (index != -1 && !def[blockIndex][index])
                                use[blockIndex][index] = true;
                        }
                    }
                        break;
                    case LARRAY: {
                        std::string *op1 = code->op1;
                        std::string *op2 = code->op2;
                        if (this->isOperandId(op1) || this->isOperandTemp(op1)) {
                            int index = -1;
                            this->getIndex(&index, funcRef, op1);
                            if (index != -1 && !def[blockIndex][index])
                                use[blockIndex][index] = true;
                        }
                        if (this->isOperandId(op2) || this->isOperandTemp(op2)) {
                            int index = -1;
                            this->getIndex(&index, funcRef, op2);
                            if (index != -1 && !def[blockIndex][index])
                                use[blockIndex][index] = true;
                        }
                    }
                        break;
                }
            }
        }
        bool flag = true;
        while (flag) {
            flag = false;
            for (int j = blockEnd - 1; j >= blockBegin; j--) {
                int blockIndex = j;
                Block *block = this->blockArray[blockIndex];
                int next1 = block->next1;
                int next2 = block->next2;
                if (next1 != -1) {
                    if (next2 != -1) {
                        for (int k = 0; k < symNum; k++) {
                            out[blockIndex][k] = in[next1][k] || in[next2][k];
                        }
                    } else {
                        for (int k = 0; k < symNum; k++) {
                            out[blockIndex][k] = in[next1][k];
                        }
                    }
                } else {
                    if (next2 != -1) {
                        for (int k = 0; k < symNum; k++) {
                            out[blockIndex][k] = in[next2][k];
                        }
                    }
                }
                for (int k = 0; k < symNum; k++) {
                    bool result = use[blockIndex][k] || (out[blockIndex][k] && !def[blockIndex][k]);
                    if (result != in[blockIndex][k]) {
                        flag = true;
                        in[blockIndex][k] = result;
                    }
                }
            }
        }
        for (int j = blockBegin; j < blockEnd; j++) {
            int blockIndex = j;
            this->dataAnalyzeOutFile << "No." << blockIndex << "基本块" << std::endl;
            symbol **symbolTab = this->funcSymbolTab[funcRef];
            this->dataAnalyzeOutFile << "use集合有：" << std::endl;
            for (int k = 0; k < symNum; k++) {
                if (use[blockIndex][k])
                    this->dataAnalyzeOutFile << *(symbolTab[k]->name) << " ";
            }
            this->dataAnalyzeOutFile << std::endl;
            this->dataAnalyzeOutFile << "def集合有：" << std::endl;
            for (int k = 0; k < symNum; k++) {
                if (def[blockIndex][k])
                    this->dataAnalyzeOutFile << *(symbolTab[k]->name) << " ";
            }
            this->dataAnalyzeOutFile << std::endl;
            this->dataAnalyzeOutFile << "out集合有：" << std::endl;
            for (int k = 0; k < symNum; k++) {
                if (out[blockIndex][k])
                    this->dataAnalyzeOutFile << *(symbolTab[k]->name) << " ";
            }
            this->dataAnalyzeOutFile << std::endl;
            this->dataAnalyzeOutFile << "in集合有：" << std::endl;
            for (int k = 0; k < symNum; k++) {
                if (in[blockIndex][k])
                    this->dataAnalyzeOutFile << *(symbolTab[k]->name) << " ";
            }
            this->dataAnalyzeOutFile << std::endl;
            this->outData[blockIndex] = new bool[symNum];
            for (int k = 0; k < symNum; k++) {
                this->outData[blockIndex][k] = out[blockIndex][k];
            }
        }
        int nodeNum = 0;
        int node2Sym[1000];
        for (int j = 0; j < symNum; j++) {
            symbol *sym = this->funcSymbolTab[funcRef][j];
            if (sym->symbolType == SIMPLESYM || sym->symbolType == PARASYM)
                node2Sym[nodeNum++] = j;
        }
        ConflictNode **nodeArray = new ConflictNode *[nodeNum];
        for (int j = 0; j < nodeNum; j++) {
            ConflictNode *node = new ConflictNode();
            nodeArray[j] = node;
            node->edgeNum = 0;
            for (int k = 0; k < nodeNum; k++) {
                node->connect[k] = false;
            }
        }
        for (int j = 0; j < nodeNum; j++) {
            ConflictNode *node1 = nodeArray[j];
            int symbolIndex1 = node2Sym[j];
            for (int k = j + 1; k < nodeNum; k++) {
                ConflictNode *node2 = nodeArray[k];
                int symbolIndex2 = node2Sym[k];
                bool conflictFlag = false;
                for (int l = blockEnd - 1; l >= blockBegin; l--) {
                    bool flag1 = in[l][symbolIndex1];
                    bool flag2 = in[l][symbolIndex2];
                    flag1 = flag1 || def[l][symbolIndex1];
                    flag2 = flag2 || def[l][symbolIndex2];
                    if (flag1 && flag2) {
                        conflictFlag = true;
                        break;
                    }
                }
                if (conflictFlag) {
                    node1->connect[k] = true;
                    node1->edgeNum++;
                    node2->connect[j] = true;
                    node2->edgeNum++;
                }
            }
        }
        int *order = new int[nodeNum];
        int orderIndex = 0;
        bool *allocFlag = new bool[nodeNum];
        bool *outFlag = new bool[nodeNum];
        for (int j = 0; j < nodeNum; j++) {
            allocFlag[j] = false;
            outFlag[j] = false;
        }
        while (orderIndex < nodeNum) {
            bool continueFlag = false;
            for (int j = 0; j < nodeNum; j++) {
                ConflictNode *node = nodeArray[j];
                if (!outFlag[j] && node->edgeNum < MAXREG) {
                    continueFlag = true;
                    order[orderIndex++] = j;
                    outFlag[j] = true;
                    for (int k = 0; k < nodeNum; k++) {
                        ConflictNode *temp = nodeArray[k];
                        if (temp->connect[j])
                            temp->edgeNum--;
                    }
                    break;
                }
            }
            if (!continueFlag) {
                int maxEdgeNumIndex = -1;
                int maxEdgeNum = -1;
                for (int j = 0; j < nodeNum; j++) {
                    if (!outFlag[j]) {
                        ConflictNode *node = nodeArray[j];
                        if (node->edgeNum >= maxEdgeNum) {
                            maxEdgeNumIndex = j;
                            maxEdgeNum = node->edgeNum;
                        }
                    }
                }
                outFlag[maxEdgeNumIndex] = true;
                allocFlag[maxEdgeNumIndex] = true;
                order[orderIndex++] = maxEdgeNumIndex;
                for (int k = 0; k < nodeNum; k++) {
                    ConflictNode *temp = nodeArray[k];
                    if (temp->connect[maxEdgeNumIndex])
                        temp->edgeNum--;
                }
            }
        }
        bool *isAdd = new bool[nodeNum];
        int *regAlloc = new int[nodeNum];
        for (int j = 0; j < nodeNum; j++) {
            isAdd[j] = false;
        }
        for (int j = nodeNum - 1; j >= 0; j--) {
            int nodeIndex = order[j];
            ConflictNode *node = nodeArray[nodeIndex];
            isAdd[nodeIndex] = true;
            if (!allocFlag[nodeIndex]) {
                bool ableFlag[MAXREG];
                for (int k = 0; k < MAXREG; k++) {
                    ableFlag[k] = true;
                }
                for (int k = 0; k < nodeNum; k++) {
                    if (node->connect[k] && isAdd[k] && !allocFlag[k]) {
                        ableFlag[regAlloc[k]] = false;
                    }
                }
                for (int k = 0; k < MAXREG; k++) {
                    if (ableFlag[k]) {
                        regAlloc[nodeIndex] = k;
                        int symbolIndex = node2Sym[nodeIndex];
                        symbol *sym = this->funcSymbolTab[funcRef][symbolIndex];
                        sym->reg = k;
                        break;
                    }
                }
            }
        }
        this->dataAnalyzeOutFile << "No." << funcRef << "函数" << std::endl;
        for (int j = 0; j < symNum; j++) {
            symbol *sym = this->funcSymbolTab[funcRef][j];
            if (sym->reg != -1)
                this->dataAnalyzeOutFile << *sym->name << "被分配了" << sym->reg << "号寄存器" << std::endl;
        }
        this->dataAnalyzeOutFile << std::endl;
        delete[] regAlloc;
        delete[] isAdd;
        delete[] outFlag;
        delete[] order;
        delete[] allocFlag;
        for (int j = 0; j < nodeNum; j++) {
            delete[] nodeArray[j];
        }
        delete[] nodeArray;
        for (int j = blockEnd - 1; j >= blockBegin; j--) {
            delete[] use[j];
            delete[] def[j];
            delete[] in[j];
            delete[] out[j];
        }
    }
    delete[] use;
    delete[] def;
    delete[] in;
    delete[] out;
}

void Compiler::getNode(ListNode **nodeList, int length, std::string *name, ListNode **listNode) {
    for (int i = 0; i < length; i++) {
        ListNode *node = nodeList[i];
        if (this->isEqual(*(node->name), *name)) {
            *listNode = node;
            return;
        }
    }
}

void Compiler::dag() {
    int oldIndex = this->midCodeIndex;
    this->midCodeIndex = 0;
    for (int i = 0; i < this->blockIndex; i++) {
        int blockIndex = i;
        int begin = this->blockBegin[i];
        int end = i + 1 >= this->blockIndex ? oldIndex : this->blockBegin[i + 1];
        int tabLength = 0;
        int nodeIndex = 0;
        ListNode *nodeTab[MAXNODE * 5];
        Node *dag[MAXNODE * 5];
        int funcRef = -1;
        for (int k = 0; k < this->funcNum; k++) {
            if (k == this->funcNum - 1) {
                funcRef = k;
                break;
            } else if (this->funcBlockBegin[k] <= blockIndex && this->funcBlockBegin[k + 1] > blockIndex) {
                funcRef = k;
                break;
            }
        }
        midCode *firstCode = this->midCodes[begin];
        if (firstCode->op != ADD && firstCode->op != SUB && firstCode->op != MUL && firstCode->op != DIV &&
            firstCode->op != RARRAY && firstCode->op != LARRAY && firstCode->op != SCAN && firstCode->op != PARA &&
            firstCode->op != PRINT) {
            this->pushMidCode(firstCode->op, firstCode->op1, firstCode->op1, firstCode->res);
            begin++;
        }
        if (end == begin)
            continue;
        if (end - 1 == begin) {
            firstCode = this->midCodes[begin];
            this->pushMidCode(firstCode->op, firstCode->op1, firstCode->op2, firstCode->res);
            continue;
        }
        int count = 0;
        midCode *endCode = this->midCodes[end - 1];
        int endIndex = 0;
        if (endCode->op == SCAN || endCode->op == ADD || endCode->op == SUB || endCode->op == MUL ||
            endCode->op == DIV || endCode->op == RARRAY || endCode->op == LARRAY || endCode->op == PARA ||
            endCode->op == PRINT)
            endIndex = end;
        else
            endIndex = end - 1;
        for (int j = begin; j < endIndex; j++) {
            midCode *code = this->midCodes[j];
            switch (code->op) {
                case ADD:
                case SUB:
                case MUL:
                case DIV:
                case RARRAY:
                case LARRAY:
                case PARA:
                case SCAN:
                case PRINT:
                    if (code->op == ADD && this->isEqual(*code->op2, ZEROSTR)) {
                        ListNode *listNode = 0;
                        this->getNode(nodeTab, tabLength, code->op1, &listNode);
                        if (listNode) {
                            Node *dagNode = dag[listNode->index];
                            if (!dagNode->isLeaf) {
                                ListNode *listNode1 = 0;
                                this->getNode(nodeTab, tabLength, code->res, &listNode1);
                                if (!listNode1) {
                                    listNode1 = new ListNode;
                                    listNode1->name = code->res;
                                    nodeTab[tabLength++] = listNode1;
                                    listNode1->index = listNode->index;
                                    this->dagOutFile << *code->res << " 与 " << *dagNode->name << " 值相等" << std::endl;
                                    count++;
                                    int index = -1;
                                    this->getIndex(&index, funcRef, code->res);
                                    if (dagNode->flag) {
                                        *dagNode->name = *code->res;
                                        dagNode->flag = false;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    ListNode *listNode1 = 0;
                    this->getNode(nodeTab, tabLength, code->op1, &listNode1);
                    if (!listNode1) {
                        Node *node = new Node();
                        node->isLeaf = true;
                        node->op = NONE;
                        node->parentNum = 0;
                        node->xIndex = -1;
                        node->yIndex = -1;
                        node->index = nodeIndex;
                        node->name = new std::string();
                        *node->name = *code->op1;
                        dag[nodeIndex++] = node;
                        listNode1 = new ListNode();
                        listNode1->name = code->op1;
                        listNode1->index = node->index;
                        nodeTab[tabLength++] = listNode1;
                    }
                    ListNode *listNode2 = 0;
                    this->getNode(nodeTab, tabLength, code->op2, &listNode2);
                    if (!listNode2) {
                        Node *node = new Node();
                        node->isLeaf = true;
                        node->op = NONE;
                        node->parentNum = 0;
                        node->xIndex = -1;
                        node->yIndex = -1;
                        node->index = nodeIndex;
                        node->name = new std::string();
                        *node->name = *code->op2;
                        dag[nodeIndex++] = node;
                        listNode2 = new ListNode();
                        listNode2->name = code->op2;
                        listNode2->index = node->index;
                        nodeTab[tabLength++] = listNode2;
                    }
                    Node *mid = 0;
                    for (int k = 0; k < nodeIndex; k++) {
                        Node *node = dag[k];
                        if (!node->isLeaf && node->op == code->op && node->xIndex == listNode1->index &&
                            node->yIndex == listNode2->index) {
                            if (code->op == LARRAY) {
                                if (this->isEqual(*code->res, *node->name)) {
                                    mid = node;
                                    count++;
                                }
                            } else if (code->op == PARA || code->op == PRINT);
                            else {
                                mid = node;
                                count++;
                                int index = -1;
                                this->getIndex(&index, funcRef, code->res);
                                if (mid->flag) {
                                    *mid->name = *code->res;
                                    mid->flag = false;
                                }
                            }
                            break;
                        }
                    }
                    if (!mid) {
                        mid = new Node();
                        mid->index = nodeIndex;
                        mid->isLeaf = false;
                        mid->name = new std::string();
                        *mid->name = *code->res;
                        mid->flag = false;
                        mid->op = code->op;
                        mid->parentNum = 0;
                        mid->xIndex = listNode1->index;
                        mid->yIndex = listNode2->index;
                        Node *node1 = dag[listNode1->index];
                        Node *node2 = dag[listNode2->index];
                        node1->parentIndex[node1->parentNum++] = nodeIndex;
                        node2->parentIndex[node2->parentNum++] = nodeIndex;
                        dag[nodeIndex++] = mid;
                    }
                    if (code->op == PARA || code->op == PRINT)
                        break;
                    ListNode *listNode3 = 0;
                    this->getNode(nodeTab, tabLength, code->res, &listNode3);
                    if (!listNode3) {
                        listNode3 = new ListNode();
                        listNode3->name = code->res;
                        nodeTab[tabLength++] = listNode3;
                        listNode3->index = mid->index;
                    } else {
                        Node *node = dag[listNode3->index];
                        listNode3->index = mid->index;
                        if (this->isEqual(*node->name, *listNode3->name)) {
                            node->flag = true;
                            for (int k = 0; k < tabLength; k++) {
                                if (nodeTab[k]->index == node->index) {
                                    *node->name = *nodeTab[k]->name;
                                    node->flag = false;
                                }
                            }
                        }
                    }
                    break;
            }
        }
        if(!count){
            for(int j=begin;j<end;j++){
                midCode *code = this->midCodes[j];
                this->pushMidCode(code->op,code->op1,code->op2,code->res);
            }
            continue;
        }
        this->dagOutFile<<"No."<<i<<"块有优化"<<std::endl;
        Node *midQueue[MAXNODE*5] = {0};
        int midLength = 0;
        for(int j=0;j<nodeIndex;j++){
            Node *node = dag[j];
            if(!node->isLeaf)
                midQueue[midLength++] = node;
        }
        for(int j=0;j<midLength;j++){
            Node *node = midQueue[j];
            std::string *mid = new std::string();
            *mid = *node->name;
            Node *listNode1 = dag[node->xIndex];
            Node *listNode2 = dag[node->yIndex];
            std::string *op1 = new std::string();
            std::string *op2 = new std::string();
            *op1 = *listNode1->name;
            *op2 = *listNode2->name;
            if(node->op == PRINT || node->op == PARA)
                this->pushMidCode(node->op,op1,op2,op1);
            else
                this->pushMidCode(node->op,op1,op2,mid);
            for(int k=0;k<tabLength;k++){
                ListNode *listNode = nodeTab[k];
                if(listNode->index == node->index && !this->isEqual(*listNode->name,*mid)){
                    if(this->isOperandTemp(listNode->name)){
                        int index = -1;
                        this->getIndex(&index,funcRef,listNode->name);
                        if(this->outData[blockIndex][index])
                            this->pushMidCode(ADD,mid,new std::string("0"),listNode->name);
                        else{
                            this->dagOutFile<<*listNode->name<<" 不活跃，被删除"<<std::endl;
                            midCode *code = this->midCodes[end-1];
                            switch (code->op){
                                case EQU:
                                case NEQU:
                                case LE:
                                case LEEQU:
                                case GRE:
                                case GREEQU: {
                                    if(this->isEqual(*code->op1,*listNode->name)){
                                        this->dagOutFile<<*code->op1<< " 被替换为了" <<*mid<<std::endl;
                                        *code->op1 = *mid;
                                    }
                                    if(this->isEqual(*code->op2,*listNode->name)){
                                        this->dagOutFile<<*code->op2<< " 被替换为了" <<*mid<<std::endl;
                                        *code->op2 = *mid;
                                    }
                                }
                                    break;
                            }
                        }
                    }
                    else if(this->isOperandId(listNode->name)){
                        int index = -1;
                        this->getIndex(&index,funcRef,listNode->name);
                        if(index == -1)
                            this->pushMidCode(ADD,mid,new std::string("0"),listNode->name);
                        else{
                            if(this->outData[blockIndex][index])
                                this->pushMidCode(ADD,mid,new std::string("0"),listNode->name);
                            else{
                                this->dagOutFile<<*listNode->name<<" 不活跃，被删除"<<std::endl;
                                midCode *code=this->midCodes[end-1];
                                switch (code->op){
                                    case EQU:
                                    case NEQU:
                                    case LE:
                                    case LEEQU:
                                    case GRE:
                                    case GREEQU: {
                                        if(this->isEqual(*code->op1,*listNode->name)){
                                            this->dagOutFile<<*code->op1<< " 被替换为了" <<*mid<<std::endl;
                                            *code->op1 = *mid;
                                        }
                                        if(this->isEqual(*code->op2,*listNode->name)){
                                            this->dagOutFile<<*code->op2<< " 被替换为了" <<*mid<<std::endl;
                                            *code->op2 = *mid;
                                        }
                                    }
                                        break;
                                }
                            }
                        }
                    } else
                        this->pushMidCode(ADD,mid,new std::string("0"),listNode->name);
                }
            }
        }
        if(endIndex == end-1){
            midCode *code = this->midCodes[end-1];
            this->pushMidCode(code->op,code->op1,code->op2,code->res);
        }
    }
}

void Compiler::optimize() {
    this->zeroAndDuplicateOptimize();
    this->blockDivide();
    this->connectBlock();
    this->outputBlock();
    this->dataFlowAnalyze();
    this->dag();
}
