/*Diego Rodríguez Romero A01741413
9 de octubre de 2023
Act 3.1 - Operaciones avanzadas en un BST*/

#include <iostream>
#include <queue>
#include <vector>

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

/*Funcion de insertar, este metodo recibe el valor del nodo que queremos insertar
y lo que hace es que va desde la raiz bajando hasta que encuentra el lugar donde dicho 
elemento debe de ir, Complejidad O(h) donde h es la altura del arbol*/
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


/*Funcion de Preorden, el metodo de visita de Preorden imprime primero el nodo actual, luego
visita el izquierdo y luego el derecho, pero es un metodo recursivo. Complejidad O(n) */
void BST::PreOrder(Node* currentNode){
    if(currentNode == NULL){
        return;
    }
    std::cout << currentNode->data << " " ;
    PreOrder(currentNode->left);
    PreOrder(currentNode->right);
}


/*FUncion de En orden. Este metodo igualmente visita el arbol pero de menor a mayor
, para hacer esto siempre visita el nodo de la izquierda primero y de igual forma es recursiva.
Complejidad O(n) */
void BST::InOrder(Node* currentNode){
    if(currentNode == NULL){
        return;
    }
    InOrder(currentNode->left);
    std::cout << currentNode->data << " " ;
    InOrder(currentNode->right);
}

/*Funcion de PostOrden. Contraria a la funcion Pre Orde, aqui primero se visita
el nodo de la derecha. Complejidad O(n) */
void BST::PostOrder(Node* currentNode){
    if(currentNode == NULL){
        return;
    }
    PostOrder(currentNode->left);
    PostOrder(currentNode->right);
    std::cout << currentNode->data << " " ;
}

/* Funcion para imprimir un arbol. Este metodo se apoya de el uso de una queue
a la que le va agregando todos los nodos que componen un nivel y los va imprimiendo,
 para despues eliminarlos y pasarse a el siguiente nivel. Complejidad O(n)*/
void BST::BFT(){
    if(Root == NULL){
        std::cout << "El arbol esta vacio\n";
        return;
    }

    queue<Node*> Q;
    Q.push(Root);

    Node *Aux;

    std::cout << "\nLevelBYLevel: \n";
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

/*Metodo SubstituteToMin. Metodo auxiliar a delete, el cual se utiliza
 cuando un nodo que se quere borrar tiene 2 hijos, los nodos cambian lugares
 COmplejidad O(n) */
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

/*Metodo delete. Metodo que se utiliza cuando queremos borrar algun nodo 
Complejidad O(n)*/
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

/* DeleteBST. Metodo para borrar el arbol entero Complejidad O(n)*/
void BST::DeleteBST(Node *&currentNode){
    if(!currentNode){
        return;
    }

    DeleteBST(currentNode->left);
    DeleteBST(currentNode->right);
}


/*Funcion visit para decidir como se visita(imprime un arbol) 
Complejidad O(n)*/
void BST::visit(int seleccion){
    if(seleccion > 4){
        std::cout << "Seleccion Invalida (Elija un numero entre 1 y 4)\n";
        return;
    }
    else if(seleccion == 1){
        std::cout << "PreOrder: ";
        PreOrder();
        std::cout << "\n";
    }
    else if(seleccion == 2){
        std::cout << "InOrder: ";
        InOrder();
        std::cout << "\n";
    }
    else if(seleccion == 3){
        std::cout << "PostOrder: ";
        PostOrder();
        std::cout << "\n";
    }
    else{
        BFT();
        std::cout << "\n";
    }
}

/*Height, regresa la altura total del arbol
Complejidad O(n) */
int BST::height(){
    int cont;
    //Si el arbol esta vacio
    if(Root == NULL){
        return -1;
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
        cont = -1;
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

/* Ancestors. Este metodo regresa todos los padres de un nodo en especifico, hasta llegar
a la raiz. Complejidad O(n)*/
bool BST::Ancestors(int &dato, Node *&currentNode){
    if(currentNode == NULL){
        std::cout << "El elemento no existe\n";
        return false;
    }

    if(currentNode->data == dato){
        return true;
    }

    if(Ancestors(dato, currentNode->left) || Ancestors(dato, currentNode->right)){
        std::cout<< currentNode->data << " " ;
        return true;
    }

    std::cout << "El elemento no existe\n";
    return false;   
}

/* whatLevelIamI.  Metodo que regresa la altura en la que se encuentra
algun nodo en especifico. Complejidad O(n)*/
int BST::whatLevelIamI(int &dato, Node *&currentNode){
    if(currentNode == NULL){
        return -1;
    }

    queue<Node*> Q;

    Q.push(currentNode);

    int cont=0;
    while(Q.empty() == false){
        int size = Q.size();

        while(size--){
            Node* Aux = Q.front();

            if(Aux->data == dato){
                return cont;
            }
            Q.pop();

            if(Aux->left != NULL){
                Q.push(Aux->left);
            }

            if(Aux->right != NULL){
                Q.push(Aux->right);
            }
        }
        cont++;
    }
    
}

int main(){
    system("cls");
    //Creamos el arbol
    BST arbol;

    std::vector<int> v={47, 60, 22, 12, 6, 13, 41, 20, 52, 16};

    //Vamos agregando nodos al arbol usando el metodo Insert()
    for(int i: v){
        arbol.Insert(i);
    }
    
    std::cout << "Visitas al arbol:\n";
    std::cout << "Visita PreOrder:\n";
    arbol.visit(1);

    std::cout << "Visita InOrder:\n";
    arbol.visit(2);

    std::cout << "Visita PostOrder:\n";
    arbol.visit(3);

    std::cout << "Visita LevelByLevel:\n";
    arbol.visit(4);

    //Borrar
    std::cout << "Borramos el nodo 60:\n";
    int a = 60;
    arbol.DeleteNode(a);
    arbol.BFT();
    std::cout << "\n";

/*
    int b = 13;
    arbol.DeleteNode(b);
    arbol.BFT();

    int c = 47;
    arbol.DeleteNode(c);
    arbol.BFT();
*/

    std::cout << "\nLa altura del arbol es: " << arbol.height() << "\n";
    
    //ancestros
    int b=6;
    std::cout << "Los ancestros de " << b << " son ";
    arbol.Ancestors(b);
    std::cout << "\n";

    //nivel
    int c=20;
    std::cout << "\nEl elemento " << c << " esta en el nivel " << arbol.whatLevelIamI(c) << "\n";

    return 0;
}


