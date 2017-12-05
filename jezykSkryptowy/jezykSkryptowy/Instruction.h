enum INSTRUCTION_TYPE {
        NORMAL,
        WHILE_LOOP,
        CONDITION
};
 
class While;
 
class Instruction {
public:
        INSTRUCTION_TYPE inst_type;
        queue<MathObject*> *output;
        //tablica wszystkich dostepnych operatorow
 
        Instruction() {
                output = new queue<MathObject*>;
        };
        virtual ~Instruction() {
                delete output;
        };
 
        virtual void SpecialExecute(OperatorTable OperatorList) = 0;
        virtual int Execute(OperatorTable OperatorList) {
 
                stack<Number*> stosONP;
        
                bool czyPrzeciwny = false;
                output->remember();
                while (!output->empty()) {
 
                        if (zliczajOperacje >= licznikOperacji)
                                break;
 
                        MathObject* object = output->pop()->data;
 
                        if (object->math_type == VARIABLE) {
                                Variable *Var = dynamic_cast<Variable*>(object);
                                
                                if (czyPrzeciwny) {
                                        if (Var->liczba.value != Nul) {
                                                stosONP.push(dynamic_cast<Unary*>(OperatorList.tab[15])->operation(&Var->liczba));
                                                czyPrzeciwny = false;
                                                zliczajOperacje++;
                                        }
                                }
                                else
                                        stosONP.push(&Var->liczba);
                        }
                        else if (object->math_type == NUMBER) {
                                if (czyPrzeciwny) {
                                        dynamic_cast<Number*>(object)->setValue(-dynamic_cast<Number*>(object)->value);
                                        stosONP.push(dynamic_cast<Number*>(object));
                                        czyPrzeciwny = false;
                                }
                                else
                                        stosONP.push(dynamic_cast<Number*>(object));
                        }
                        else if (object->math_type == OPERATOR) {
                                if (dynamic_cast<Unary*>(object)) {
                                        czyPrzeciwny = true;
                                        continue;
                                }
                                zliczajOperacje++;
                                if (zliczajOperacje >= licznikOperacji)
                                        break;
 
                                Operator *aktualnyOperator = dynamic_cast<Operator*>(object);//OperatorList.getOperator(object->key);
                                if (aktualnyOperator->arg_type == TWOARG) {
                                        Number *A = stosONP.current();
                                        stosONP.pop();
                                        Number *B = stosONP.current();
                                        stosONP.pop();
                                        stosONP.push(aktualnyOperator->operation(B, A));
                                }
                                else {
                                        Number *A = stosONP.current();
                                        stosONP.pop();
                                        stosONP.push(dynamic_cast<NOT*>(aktualnyOperator)->operation(A));
                                }
                                //}
                        }
                }
                output->recall();
                //oproznianie stosu ONP
                Number *toReturn = new Number();
                while (stosONP.current()) {
                        toReturn = stosONP.current();
                        stosONP.pop();
                }
 
                //RETURN LAST ONP VALUE
                return toReturn->value;
        }
};
 
class SingleInstruction : public Instruction {
public:
        SingleInstruction() {
                inst_type = NORMAL;
        }
 
        void SpecialExecute(OperatorTable OperatorList) {
                output->remember();
                Execute(OperatorList);
                output->recall();
        }
};
 
 
class Condition : public Instruction {
public:
        queue<Instruction*> *kolejkaInstrukcji;
        Condition() {
                inst_type = CONDITION;
                kolejkaInstrukcji = new queue<Instruction*>;
        };
        ~Condition() {
                delete kolejkaInstrukcji;
        }
 
        void SpecialExecute(OperatorTable OperatorList) {
                node<Instruction*> *warunek = kolejkaInstrukcji->firstElement();
                kolejkaInstrukcji->remember();
 
                node<Instruction*> *pointer = kolejkaInstrukcji->head->next;
 
                if (warunek->data->Execute(OperatorList) != Nul) {
                        zliczajOperacje++;
                        while (pointer != NULL) {
 
                                pointer->data->SpecialExecute(OperatorList);
                                pointer = pointer->next;
 
                                if (zliczajOperacje >= licznikOperacji)
                                        break;
                        }
                        kolejkaInstrukcji->recall();
                        pointer = kolejkaInstrukcji->head->next;
                }
                else {
                        if (zliczajOperacje >= licznikOperacji)
                                return;
                        zliczajOperacje++;
                }
        }
};
 
class While : public Instruction {
public:
        queue<Instruction*> *kolejkaInstrukcji;
 
        While() {
                inst_type = WHILE_LOOP;
                kolejkaInstrukcji = new queue<Instruction*>;
        };
 
        ~While() {
                delete kolejkaInstrukcji;
        }
 
        void SpecialExecute(OperatorTable OperatorList) {
 
                node<Instruction*> *warunek = kolejkaInstrukcji->firstElement();
                kolejkaInstrukcji->remember();
 
                node<Instruction*> *pointer = kolejkaInstrukcji->head->next;
 
 
                while (warunek->data->Execute(OperatorList) != Nul) {
                        zliczajOperacje++;
                        while (pointer != NULL) {
 
                                pointer->data->SpecialExecute(OperatorList);
                                pointer = pointer->next;
 
                                if (zliczajOperacje >= licznikOperacji)
                                        break;
                        }
                        kolejkaInstrukcji->recall();
                        pointer = kolejkaInstrukcji->head->next;
                }
 
                if (zliczajOperacje >= licznikOperacji)
                        return;
                zliczajOperacje++;
        }
};
