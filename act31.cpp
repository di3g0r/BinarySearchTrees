#include <iostream>
#include <queue>

using std::queue;

//Creamos la estructura Nodo

struct Node{
    int data;
    Node *left,*right;

    Node(int d): data(d),left(NULL),right(NULL){}
};

//Implmentamos un Binary Search Tree
class BST{
    private:
        Node *Root;

        void Insert(int&, Node*&);
        void InOrder(Node*);
        void PreOrder(Node*);
        void PostOrder(Node*);
        void DeleteNode(int&, Node*&);
        bool Ancestors(int&, Node*&);
        int whatLevelIamI(int&, Node*&);
        //int height(Node*&);

    public:
        BST():Root(NULL){}
        ~BST(){
            DeleteBST(Root);
            std::cout<<"\nDestructor: BST Borrado\n";
        }

        void Insert(int &value) { Insert(value, Root); }
        

        void InOrder() { InOrder(Root); }
        void PreOrder() { PreOrder(Root); }
        void PostOrder() { PostOrder(Root); }
      

        void BFT();

        void visit(int); //Visitar
        int height(); /*{height(Root); };*/ //Regresa la altura dela arbol
        bool Ancestors(int &dato) { Ancestors(dato, Root); }
        int whatLevelIamI(int &dato) {whatLevelIamI(dato, Root); }
        
        
        void SubstituteToMin(Node*&, Node*&);
        void DeleteNode(int &value) { DeleteNode(value, Root); }

        void DeleteBST(Node*&);
};

//Funcion de insertar
void BST::Insert(int &value, Node *&currentNode){
    if(currentNode == NULL){
        currentNode = new Node(value);
    }

    else{
        if(value < currentNode->data){
            Insert(value, currentNode->left);
        }
        else if(value > currentNode->data){
            Insert(value, currentNode->right);
        }
        else{
            std::cout << "El elemento esta repetido, este arbol no acepta valores repetidos\n";
        }
    }
}


//Funcion de Preorden
void BST::PreOrder(Node* currentNode){
    if(currentNode == NULL){
        return;
    }
    std::cout << "PreOrder: ";
    std::cout << currentNode->data << " " ;
    PreOrder(currentNode->left);
    PreOrder(currentNode->right);
}


//FUncion de En orden
void BST::InOrder(Node* currentNode){
    if(currentNode == NULL){
        return;
    }

    std::cout << "InOrder: ";
    InOrder(currentNode->left);
    std::cout << currentNode->data << " " ;
    InOrder(currentNode->right);
}

//Funcion de PostOrden
void BST::PostOrder(Node* currentNode){
    if(currentNode == NULL){
        return;
    }

    std::cout << "PostOrder: ";
    PostOrder(currentNode->left);
    PostOrder(currentNode->right);
    std::cout << currentNode->data << " " ;
}

//Funcion para imprimir un arbol
void BST::BFT(){
    if(Root == NULL){
        std::cout << "El arbol esta vacio\n";
        return;
    }

    queue<Node*> Q;
    Q.push(Root);

    Node *Aux;

    std::cout << "LevelBYLevel: \n";
    while(!Q.empty()){
        Q.push(NULL);

        Aux = Q.front();
        while(Aux != NULL){
            std::cout << Aux->data << " ";

            if(Aux->left != NULL){
                Q.push(Aux->left);
            }
            if(Aux->right != NULL){
                Q.push(Aux->right);
            }
            Q.pop();
            Aux = Q.front();
        }
        Q.pop();

        std::cout << "\n";
    }
}

void BST::SubstituteToMin(Node *&aptAux, Node *&aptNode){
    if(aptAux->left != NULL){
        SubstituteToMin(aptAux->left, aptNode);
    }
    else{
        aptNode->data = aptAux->data;
        aptNode = aptAux;
        aptAux = aptAux->right;
    }
}

void BST::DeleteNode(int &value, Node *&currentNode){
     if(currentNode == NULL){
        std::cout << "El BST esta vacio\n";
    }

    else{
        if(value < currentNode->data){
            DeleteNode(value, currentNode->left);
        }
        else if(value > currentNode->data){
            DeleteNode(value, currentNode->right);
        }
        else{
            Node *apAux = currentNode;

            if(apAux->right == NULL){ //Solo tiene hijo izquierdo
                currentNode = apAux->left;
            }
            if(apAux->left == NULL){ //Solo tiene hijo derecho
                currentNode = apAux->right;
            }
            if(apAux->left != NULL && apAux->right != NULL){//Tiene los 2 hijos
                SubstituteToMin(currentNode->right, apAux);
        }
            std::cout << "\nLa llave a borrar: " << value << "\n";
            std::cout << "\nEl elemento fue borrado con la llave: " << apAux->data << "\n";
            delete apAux;
    }
}
}

void BST::DeleteBST(Node *&currentNode){
    if(!currentNode){
        return;
    }

    DeleteBST(currentNode->left);
    DeleteBST(currentNode->right);
}


//Funcion visit para decidir como se visita(imprime un arbol)
void BST::visit(int seleccion){
    if(seleccion > 4){
        std::cout << "Seleccion Invalida (Elija un numero entre 1 y 4)\n";
        return;
    }
    else if(seleccion == 1){
        PreOrder();
    }
    else if(seleccion == 2){
        InOrder();
    }
    else if(seleccion == 3){
        PostOrder();
    }
    else{
        BFT();
    }
}

//Height, regresa la altura del arbol
int BST::height(){
    int cont;
    //Si el arbol esta vacio
    if(Root == NULL){
        return NULL;
        std::cout << "El arbol esta vacio\n";
    }

    Node *raiz;
    raiz = Root;

    //Si el arbol solo tiene raiz
    if(raiz->left == NULL && raiz->right == NULL){
        return 0;
    }
    else{
        queue<Node*> Q;
        Q.push(Root);
        cont = 0;
        Q.push(NULL);

        while(!Q.empty()){
            Node* Aux = Q.front();
            Q.pop();

            if(Aux == NULL){
                cont++;
            }

            if(Aux != NULL){
                if(Aux->left){
                    Q.push(Aux->left);
                }
                if(Aux->right){
                    Q.push(Aux->right);
                }
            }
            else if(!Q.empty()){
                Q.push(NULL);
            }
        }   
    }
        return cont;
}


bool BST::Ancestors(int &dato, Node *&currentNode){
    if(currentNode == NULL){
        std::cout << "El elemento no existe\n";
        return false;
    }

    if(currentNode->data == dato){
        std::cout << "El elemento es la raiz\n";
        return true;
    }

    if(Ancestors(dato, currentNode->left) || Ancestors(dato, currentNode->right)){
        std::cout<< currentNode->data << ", " ;
        return true;
    }

    std::cout << "El elemento no existe\n";
    return false;   
}

int nivel = 0;

int BST::whatLevelIamI(int &dato, Node *&currentNode){
    if(currentNode == NULL){
        std::cout << "El elemento no existe\n";
        return NULL;
    }

    

    while(currentNode->data != dato){
        if(currentNode->data == dato){
            return nivel;
        }
        else{
            if(whatLevelIamI(dato, currentNode->left) == dato && whatLevelIamI(dato, currentNode->right) == dato){
                nivel++;
            }
        }
    }
    return nivel;
}


int main(){
    std::cout<<"Hola\n";
    return 0;
}


