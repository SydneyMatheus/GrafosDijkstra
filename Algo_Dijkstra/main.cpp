/// Disciplina: 3643 - GRAFOS
/// Atividade: Avaliação 3 – Aplicação com o algoritmo de Dijkstra.
/// Programa 03
/// Acadêmico: Sydney Matheus de Souza

#define MAX_RANGE 2147483647

#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <locale>
#include <sstream>

#include <numeric>
#include <algorithm>

using namespace std;

///Posição relativa do vertice passado dentro do vetor de vértices
int posDoVertice ( int vetInicial, vector<int> vertices)
{
    for(uint32_t i = 0; i<vertices.size(); i++)
    {
        if(vertices[i] == vetInicial) //Percorre cada vértice e compara com o passado para retornar a posição deste no vertice
            return i;
    }
    return false;
}

///Algoritmo de busca BSF
int AlgoBSF(vector<vector<int>> matriz, int vetInicial, int vetBusca, vector<int> vertices, vector<bool> &visitados)
{
    queue<int> fila;
    int i, j = 0;

    i = posDoVertice(vetInicial, vertices);//defini o "i" para o vertice de inicio definido
    visitados[i] = 1;//marca o vertice que iniciára a busca como visitado inserindo 1 em sua posição

    cout<<"Visitou: "<<vertices[i]<<endl;

    while(j<(matriz.size()*matriz.size()))
    {
        int soma = 0;
        for(uint32_t w = 0; w<visitados.size();w++)//Passa por todos os visitados para saber se ja foram todos visitados
        {
            soma+= visitados[w];
            if(soma==visitados.size())
                return true;
        }

        if(matriz[i][j]>0 && !visitados[j])//Se tiver alguma ligação e não tiver sido visitado o vertice é visitado
        {
                fila.push(j);//adiciona na fila o vertice visitado
                visitados[j]=1;//marca o vertice como visistado
                cout<<"Visitou: "<<vertices[j]<<endl;
                if(vertices[j] == vetBusca || vertices[i] == vetBusca) //Se achar o vertice buscado plota e termina a função
                {
                    cout<<endl<<"Vertice Achado! ("<<vertices[j]<<")"<<endl;
                    return true;
                }
        }
        if((matriz.size()-1)==j) //se tiver chego ao fim da linha da matriz desempilha para prosseguir
        {
            i=fila.front();//linha é definida para o item do topo da fila
            j=-1;
            if(fila.size()>0)
            {
                fila.pop();//remove o vertice que será visitado da fila
            } else //se a fila não tiver mais itens verifica se algum vertice ainda não foi visitado
            {
                uint32_t w;
                for(w = 0; w<matriz.size(); w++)//Após chegar ao fim de um caminho verifica se não tem nenhuma ilha
                {
                    if(!visitados[w])
                        break;
                }
                i = w; //Acha algum vertice não visitado e defini a linha para ele
                visitados[i] = 1; //marca o vertice encontrado como visitado
                cout<<"Visitou: "<<vertices[i]<<endl;
                if(vertices[j] == vetBusca || vertices[i] == vetBusca) //Se achar o vertice buscado plota e termina a função
                {
                    cout<<endl<<"Vertice Achado! ("<<vertices[i]<<")"<<endl;
                    return true;
                }
            }
        }
        j++;
    }
    return true;
}

///Algoritmo de busca DSF
int AlgoDSF(vector<vector<int>> matriz, int vetInicial, int vetBusca, vector<int> vertices, vector<bool>& visitados)
{
    stack<int> pilha;
    int i, j = 0;

    i = posDoVertice(vetInicial, vertices);//define a linha da matriz para o vertice inicial
    pilha.push(i);//insere na pilha o vértice de inicio
    visitados[i] = 1;//marca o vértice de inicio como visitado

    cout<<"Visitou: "<<vertices[i]<<endl;
    while(j<(matriz.size()*matriz.size()))
    {
        int soma = 0;

        for(uint32_t w = 0; w<visitados.size();w++)//se já tiver passado por todos os visitados retorna para o main
        {
            soma+= visitados[w];
            if(soma==visitados.size())
                return true;
        }

        //Se tiver ao fim da matriz e a posição for zero ou se tiver ao fim e ja tiver sido visitado a ligação daquela posição
        if(((matriz.size()-1)==j && matriz[i][j]==0)||((matriz.size()-1)==j && visitados[j]))
        {
            pilha.pop();//remove o item da pilha

            if(!pilha.empty())//se a pilha não tiver vazia define a nova linha e volta coluna para zero
            {
                i=pilha.top();
                j=-1;
            } else//se estiver vazia verifica se algum vértice ainda não foi visitado
            {
                uint32_t w;
                for(w = 0; w<matriz.size(); w++)
                {
                    if(!visitados[w])
                        break;
                }
                i = w;//define a posição para o vértice não visitado
                j=-1;
                visitados[i] = 1;//marca o vértice como visitado
                cout<<"Visitou: "<<vertices[i]<<endl;
                if(vertices[j] == vetBusca || vertices[i] == vetBusca)//Se for o vértice buscado encerra
                {
                    cout<<endl<<"Vertice Achado! ("<<vertices[i]<<")"<<endl;
                    return true;
                }
            }
        } else if(matriz[i][j]>0 && !visitados[j])//se tiver uma ligação na posição e não tiver sido visitado
        {
            pilha.push(j);//insere na pilha
            visitados[j] = 1;//marca o vértice como visitado
            cout<<"Visitou: "<<vertices[j]<<endl;
            if(vertices[j] == vetBusca || vertices[i] == vetBusca)//Se for o vértice buscado encerra
            {
                cout<<endl<<"Vertice Achado! ("<<vertices[j]<<")"<<endl;
                return true;
            }
            i = j;//vai para o vértice a qual tem ligação com este atual
            j = -1;
        }
    j++;
    }
    return true;
}

///Verefica se a posição da matriz corresponde a alguma ligação informada anteriormente
bool verifyNDir(int a, int b, int aa, int bb) //Como é para grafo não dirigido a condição de ida e volta deve ser garantina
{                                             //Nesse caso o algoritmo testa se a posição informada tem ligação com o pontos
    if((a) == aa && (b) == bb)            //informados ou contrário dos pontos também
        return true;
    else if((a) == bb && (b) == aa)
        return true;
    return false;
}

///Verefica se a posição da matriz corresponde a alguma ligação informada anteriormente
bool verifyDir(int a, int b, int aa, int bb)//Mesmo do NDir (Ñ Dirigida) porém para Dirigida
{                                           //Recebe a posição do vector que é relativa a posição da matriz
    if((a) == aa && (b) == bb)              //verifica se a posição do vector é igual a posição da liga informada
        return true;                        //e retorna true se sim

    return false;
}

void LinhaParaVetor(string linha, vector<int>& vec)
{
    stringstream stream;
    int numero;

    stream.str(linha);//facriona a partir dos espaços entre os números na linha

  	while (stream >> numero)//operador extract remove do stream para inserir ao objeto número
        vec.push_back(numero);//que vai para dentro do vector em seguida

    stream.clear();//limpa o stream
}

void gerarMatriz(int& vetInicial,int& vetBusca,int& tipoBusca,int& dirigida,vector<int>& vertices,vector<int>& liga, bool& busca, bool& conect, bool& dijkstra)
{
    string linha;
    int op = 0;
    vetBusca = 0;
    busca = 0;
    conect = 0;

    while(true)
    {
        cout<<endl<<"\t\tConectividade de Grafos"<<endl<<endl<<endl<<endl<<endl<<endl;
        cout<<endl<<"1 - Adicionar vertices"<<endl;
        cout<<endl<<"2 - Buscar vértice"<<endl;
        cout<<endl<<"3 - Conectividade"<<endl;
        cout<<endl<<"4 - Menor Caminho (Dijkstra)"<<endl;
        cin>>op;

        if(op == 1)
        {
            cin.sync();
            cout<<"Digite os vértices, separando por espaços (Ex: 1 2): "<<endl;
            getline(cin, linha);
            cout<<endl;

            LinhaParaVetor(linha, vertices);

            cin.sync();
            cout<<"Digite as ligações dos vértices, separando por espaços (Ex: 1 2 P, sendo P o peso): "<<endl;
            getline(cin, linha);
            cout<<endl;

            LinhaParaVetor(linha, liga);

            cin.sync();
            cout<<"Informe se a matriz é dirigida 0 = Não e 1 = Sim: "<<endl;
            cin>>dirigida;
        }

        if(op == 2)
        {
            cin.sync();
            cout<<"Digite o vertice de inicio da busca: (-1 para percorrer a matriz)"<<endl;
            cin>>vetInicial;
            cout<<endl;

            cin.sync();
            cout<<"Digite o vertice a ser buscado: (-1 para percorrer a matriz)"<<endl;
            cin>>vetBusca;
            cout<<endl;
            busca = 1;

            break;
        }

        if(op == 3)
        {
            cin.sync();
            cout<<"Digite o vertice de inicio da busca:"<<endl;
            cin>>vetInicial;
            cout<<endl;

            conect=1;
            break;
        }

        if(op == 4)
        {
            cin.sync();
            cout<<"Digite o vertice de inicio da busca:"<<endl;
            cin>>vetInicial;
            cout<<endl;
            dijkstra = 1;

            break;
        }

        op = 0;
        system("cls");
    }

    system("cls");
}

void PopulaMatriz (vector<vector<int>>& matriz, int dirigida, vector<int> vertices, vector<int> liga, bool peso)
{
    for(uint32_t i = 0; i < matriz.size(); ++i)
    {
        for(uint32_t j = 0; j < matriz.size(); ++j)
        {
            for(uint32_t k = 0; k<liga.size();k+=(2+peso))///deveria ser até liga.size()-1 e ou liga.size()-(1 + (1 * peso)) (acho)
            {
                if(!dirigida) //Para grafo não dirigido
                {
                    if(verifyNDir(vertices[i],vertices[j],liga[k],liga[k+1]))
                    {
                        matriz[i][j] = 1+((liga[k+2]-1)*peso);
                        break;
                    } else
                    {
                        matriz[i][j] = 0; //Caso não tenha ligação na presente posição
                    }
                }   else if(dirigida)//Para grafo dirigido
                {
                   if(verifyDir(vertices[i],vertices[j],liga[k],liga[k+1]))//Faz uma chamada de função que verifica se tem ligação na presente posição
                    {
                        matriz[i][j] = 1+((liga[k+2]-1)*peso);
                        break;
                    }   else
                    {
                        matriz[i][j] = 0; //Caso não tenha ligação na presente posição
                    }
                }
            }
        }
    }
}

bool FechoTranDireto(vector<vector<int>> matriz, int vetInicial, vector<int> vertices, vector<int> &nivelFeixoDir)
{
    queue<int> fila;
    int i, j = 0, soma = 0, nivel=1;

    i = posDoVertice(vetInicial, vertices);//defini o "i" para o vertice de inicio definido
    nivelFeixoDir[i] = 0;

    cout<<"Visitou: "<<vertices[i];

    while(j < matriz.size())
    {
        if(matriz[i][j]>0 && nivelFeixoDir[j]==-1)//Se tiver alguma ligação e não tiver sido visitado o vertice é visitado
        {
                fila.push(j);//adiciona na fila o vertice visitado
                nivelFeixoDir[j] = nivelFeixoDir[i]+1;//nivel;

                cout<<"   Visitou: "<<vertices[j];
        }

        if((matriz.size()-1)==j && fila.size()>0) //se tiver chego ao fim da linha da matriz desempilha para prosseguir
        {
            i=fila.front();//linha é definida para o item do topo da fila
            j=-1;
            fila.pop();//remove o vertice que será visitado da fila
        }
        j++;
    }

    return false;
}

bool FechoTranInverso(vector<vector<int>> matriz, int vetInicial, vector<int> vertices, vector<int> &nivelFeixoInv)
{
    queue<int> fila;
    int i, j = 0, nivel=1;

    i = posDoVertice(vetInicial, vertices);//defini o "i" para o vertice de inicio definido
    j = i;

    nivelFeixoInv[i] = 0;

    cout<<"Visitou: "<<vertices[i];

    while(i < matriz.size())
    {
        if(matriz[i][j]>0 && nivelFeixoInv[i]==-1)//Se tiver alguma ligação e não tiver sido visitado o vertice é visitado
        {
                fila.push(i);//adiciona na fila o vertice visitado
                nivelFeixoInv[i] = nivelFeixoInv[j]+1;//nivel;
                cout<<"   Visitou: "<<vertices[i];
        }
        if((matriz.size()-1)==i && fila.size()>0) //se tiver chego ao fim da linha da matriz desempilha para prosseguir
        {
            j=fila.front();//linha é definida para o item do topo da fila
            i=-1;
            fila.pop();//remove o vertice que será visitado da fila
        }
        i++;
    }
    return false;
}

int Intersec(vector<vector<int>> matriz, vector<int> vertices, vector<int> nivelFeixoDir, vector<int> nivelFeixoInv,  vector<int> liga,int dirigida, vector<bool> &vertItersec, bool peso)
{
    vector<vector<int>> matrizAux; //Cria objeto MATRIZ que é uma coleção de Vectors do tipo bool
    vector<int> verticesAux;
    matrizAux = matriz;
    verticesAux = vertices;

    for(int i = 0; i<verticesAux.size();i++)
    {
        if((nivelFeixoDir[i]==-1 || nivelFeixoInv[i]==-1))
        {
            verticesAux.erase(verticesAux.begin()+i);
            nivelFeixoDir.erase(nivelFeixoDir.begin()+i);
            nivelFeixoInv.erase(nivelFeixoInv.begin()+i);
            i = -1;
        } else {
            int j = posDoVertice(verticesAux[i],vertices);
            vertItersec[j] = 1;
        }
    }

    matrizAux.resize(verticesAux.size());
    for( auto &linha : matrizAux )
        linha.resize(verticesAux.size());

    PopulaMatriz(matrizAux,dirigida,verticesAux,liga, peso);

    cout<<endl<<"  ";
        for(uint32_t i = 0; i<matrizAux.size();++i) //Imprime o número dos vértices
            cout<<verticesAux[i]<<" ";

        cout<<endl;

    for(uint32_t i = 0; i < matrizAux.size(); ++i) //Faz impressão da matriz
    {
        for(uint32_t j = 0; j < matrizAux.size(); ++j)
        {
            if(j==0)
            {
                cout<<verticesAux[i]<<" ";//Coloca o número dos vértices
            }
            cout << matrizAux[i][j] << ' ';
        }
        cout << '\n';
    }
    //printMatriz(matrizAux, verticesAux);

    return true;
}

void printMatriz(vector<vector<int>> matriz,  vector<int> vertices)
{
    cout<<endl<<"   ";
    for(uint32_t i = 0; i<matriz.size();++i) //Imprime o número dos vértices
        cout<<vertices[i]<<"  ";

    cout<<endl;

    for(uint32_t i = 0; i < matriz.size(); ++i) //Faz impressão da matriz
    {
        for(uint32_t j = 0; j < matriz.size(); ++j)
        {
            if(j==0)
                cout<<vertices[i]<<"  ";//Coloca o número dos vértices
            cout << matriz[i][j] <<" ";
            if(matriz[i][j]<10)
                cout<<' ';
        }
        cout<<endl;
    }
}

void PopulaVector (int tamMax, vector<auto>& vet, int valor)
{
    for(uint32_t j = 0; j<tamMax; j++)
        vet.push_back(valor); //popula e cria as posições do vector visitados cada posição recebe 0
}

bool Dijkstra(vector<vector<int>> matriz, int vetInicial, vector<int> vertices,vector<bool>& visitados)
{
    int i = 0, j = 0, prox = -1, index = 0, sair = 1;
    vector<int> estimativa;
    vector<int> precedente;
    vector<vector<int>> auxMatriz;

    auxMatriz=matriz;

    for(int i = 0; i<matriz.size();i++)
        for(int j=0; j<matriz.size();j++)
            auxMatriz[i][j]=0;

    PopulaVector(matriz.size(), estimativa, -1);
    PopulaVector(matriz.size(), precedente, -2);

    i = posDoVertice(vetInicial, vertices);//defini a posição relativa "i" para o vertice de inicio definido
    estimativa[i] =  0;
    precedente[i] = -1;
    visitados[i]  =  1;
    index = i;

    while(accumulate(visitados.begin(), visitados.end(), 0)<visitados.size() && sair!=0)
    {
        if(matriz[i][j]!=0 && !visitados[j])
        {
            if((estimativa[j]==-1) || ((estimativa[i]+matriz[i][j])<estimativa[j]))
            {
                estimativa[j] = matriz[i][j]+estimativa[i];
                precedente[j] = vertices[i];
            }
        }

        if((matriz.size()-1)==j && sair!=0)
        {
            prox = MAX_RANGE;
            for(int i = 0; i <estimativa.size(); i++)
            {
                if(estimativa[i]<prox)
                {
                    if(visitados[i]==0 && estimativa[i]!=-1)
                    {
                        prox = estimativa[i];
                        index=i;
                    }
                }
            }

            if(sair!=0)
            {
                cout<<endl<<"Vertice: "<<vertices[i]<<endl<<"Vertices:   ";
                for(int i=0;i<estimativa.size();i++)
                    cout<<vertices[i]<<"  ";
                cout<<endl<<"Estimativa: ";
                for(int i=0;i<estimativa.size();i++)
                {
                    if(estimativa[i]<0)
                        cout<<"  ";
                    else
                        cout<<estimativa[i]<<' ';
                    if (estimativa[i]<10)
                        cout<<' ';
                }
                cout<<endl<<"Precedente: ";
                for(int i=0;i<precedente.size();i++)
                {
                    if(precedente[i]==-1)
                        cout<<"- ";
                    else if (precedente[i]==-2)
                        cout<<"  ";
                    else
                        cout<<precedente[i]<<' ';
                    if (precedente[i]<10)
                        cout<<' ';
                }
                cout<<endl<<endl;
            }

            sair = i-index;
            if (accumulate(visitados.begin(), visitados.end(), 0)==1 && sair == 0)
                cout<<endl<<"Não existe caminhos a partir deste vertice."<<endl<<endl;

            i = index;
            j=-1;
            visitados[i]=1;
        }
        j++;
    }

    ///Printa Grafo
    cout<<endl<<"Grafo com menor caminho (Dijkstra)"<<endl;
    for(uint32_t i = 0; i < matriz.size(); ++i)
    {
        if(precedente[i]>-1)
            auxMatriz[posDoVertice(precedente[i], vertices)][posDoVertice(vertices[i], vertices)] =
                matriz[posDoVertice(precedente[i], vertices)][posDoVertice(vertices[i], vertices)];
    }

    printMatriz(auxMatriz,vertices);
    return true;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int vetInicial = 7, vetBusca = 0, tipoBusca = 0, dirigida = 1;
    bool sair = 0, naoConexo=1, busca=0, conect=0, peso=1, dijkstra = 1;
    vector<vector<int>> matriz; //Cria objeto MATRIZ que é uma coleção de Vectors do tipo bool
    vector<bool> visitados;
    vector<int> deletVert;
    vector<int> deletLiga;
    vector<int> vertices={1,2,3,4,5,6,7};//={0,1,2,3,4};//{0,1,2,3,4,5,6,7};//{1,2,3,4,5,6};//{0,1,2,3,4};//{1,2,3,4,5,6,7};//5{1,2,3,4,5,6,7};//4{1,2,3,4,5,6};//3{1,2,3,4,5,6};//1{1,2,3,4,5}; //Vetor para todos os vértices
    vector<int> liga{1,2,2,1,4,1,2,4,3,2,5,10,3,1,4,3,6,5,4,3,2,4,5,2,4,6,8,4,7,4,5,7,6,7,6,1};//={1,2,7,1,3,11,1,4,3,2,4,1,4,1,1,4,3,3};//{0,3,2,1,0,3,1,2,6,1,5,6,2,4,4,2,6,4,3,5,7,4,2,6,5,3,3,5,6,5};//{1,2,10,1,4,5,2,3,1,2,4,2,3,5,4,4,2,3,4,3,9,4,5,2,5,1,7,5,3,6};//{0,1,5,0,2,10,0,4,2,2,3,10,3,1,1,3,4,2,4,0,3,4,1,2,4,2,7,4,3,5};//{1,2,2,1,4,1,2,4,3,2,5,10,3,1,4,3,6,5,4,3,2,4,5,2,4,6,8,4,7,4,5,7,6,7,6,1};//5{1,4,2,3,3,7,4,5,5,1,5,6,6,3,7,2,7,6};//4{1,2,2,3,3,1,3,6,4,6,6,5,5,4};//3{1,2,2,3,3,1,4,6,6,5,5,4};//1{1,2,1,3,2,3,2,4,2,5,4,5};//  //Vetor para ligações entre os vertices
    vector<bool> vertItersec;
    //1 2 7 1 3 11 1 4 3 2 4 1 4 1 1 4 3 3
    //gerarMatriz(vetInicial, vetBusca, tipoBusca, dirigida, vertices, liga, busca, conect, dijkstra); //Solicita ao usuário dados para a matriz
    peso=dijkstra;

    cout<<endl<<"Vértice de inicio: "<<vetInicial<<endl;

    if(vetBusca!= -1)
    {
        cout<<endl<<"Vértice a ser buscado: "<<vetBusca<<endl;
    }
    cout<<endl<<endl;

    for(uint32_t i = 0; i < vertices.size(); ++i)//Cria os vetores que serão as Colunas
        matriz.push_back(vector<int>());

    for(uint32_t i = 0; i < vertices.size(); ++i) //Cria e popula as linhas que passam a "existir"
        for(uint32_t j = 0; j < vertices.size(); ++j)
            matriz[i].push_back(j);

    PopulaVector(matriz.size(), visitados, 0);//popula e cria as posições do vector visitados cada posição recebe 0
    PopulaVector(matriz.size(), vertItersec, 0);

    while(true)
    {
        //Determina as ligações dentro da matriz a partir das ligações fornecidas
        PopulaMatriz(matriz,dirigida,vertices,liga, peso);
        printMatriz(matriz, vertices);

        if(dijkstra)
            Dijkstra(matriz,  vetInicial, vertices, visitados);

        dijkstra=0;
        cout<<endl<<endl<<"Matriz de Adjacência"<<endl<<"  ";

        printMatriz(matriz, vertices);

        vector<int> nivelFeixoDir;
        vector<int> nivelFeixoInv;

        cout<<"______________________________________________________________________________________"<<endl;
        if(conect)
        {
            while (!sair)
            {
                nivelFeixoDir.resize(0,0);
                nivelFeixoInv.resize(0,0);
                for(uint32_t i = 0; i<matriz.size(); i++)
                    nivelFeixoDir.push_back(-1); //popula e cria as posições do vector visitados cada posição recebe 0

                for(uint32_t i = 0; i<matriz.size(); i++)
                    nivelFeixoInv.push_back(-1); //popula e cria as posições do vector visitados cada posição recebe 0

                cout<<endl<<"     Fecho Transitivo Direto"<<endl;
                FechoTranDireto(matriz, vetInicial, vertices, nivelFeixoDir);

                cout<<endl<<"Níveis:   ";
                for(int i = 0; i< matriz.size();i++)
                {
                    if(nivelFeixoDir[i]==-1)
                    {
                        cout<<"["<<vertices[i]<<"]:"<<"   ";
                    } else
                    {
                        cout<<"["<<vertices[i]<<"]:"<<nivelFeixoDir[i]<<"   ";
                    }
                }
                cout<<endl<<endl;

                cout<<endl<<"     Fecho Transitivo Inverso"<<endl;
                FechoTranInverso(matriz, vetInicial, vertices, nivelFeixoInv);

                cout<<endl<<"Níveis:   ";
                for(int i = 0; i< matriz.size();i++)
                {
                    if(nivelFeixoInv[i]==-1)
                    {
                        cout<<"["<<vertices[i]<<"]:"<<"   ";
                    } else
                    {
                        cout<<"["<<vertices[i]<<"]:"<<nivelFeixoInv[i]<<"   ";
                    }
                }
                cout<<endl<<endl;

                cout<<endl<<"Matriz/ Subgrafo";
                Intersec(matriz,vertices,nivelFeixoDir,nivelFeixoInv, liga, dirigida, vertItersec, peso);

                for(int i = 0; i<matriz.size();i++)
                {
                    if(!vertItersec[i])
                    {
                       vetInicial = vertices[i];
                       sair = 0;
                       break;
                    }
                    sair = 1;
                }
                int cont = 0;
                if(sair)
                {
                    for(int i = 0; i< matriz.size();i++)
                    {
                        if(nivelFeixoDir[i] ==-1 || nivelFeixoInv[i]==-1)
                        {
                            cout<<endl<<"Grafo não conexo!"<<endl;
                            break;
                        }
                        else
                        {
                            cont ++;
                        }
                        if(cont == nivelFeixoDir.size())
                        {
                            cout<<endl<<"Grafo conexo!"<<endl;
                        }
                    }
                }
                cout<<"______________________________________________________________________________________"<<endl;
            }
        }
        conect = 0;

        system("pause");

        if(busca==1)
        {
            cout<<endl<<"\tAlgotitimo DSF\t"<<endl;
            AlgoDSF(matriz, vetInicial, vetBusca, vertices, visitados);

            visitados.resize(0,0);
            visitados.resize(matriz.size());

            cout<<endl<<"\tAlgotitimo BSF\t"<<endl;
            AlgoBSF(matriz, vetInicial, vetBusca, vertices, visitados);
        }
        busca = 0;
        uint16_t removerVert=0, addVert=0, removerLiga=0, addLiga=0;
        string linha;

        cin.sync();
        cout<<endl<<"Deseja adicionar vertices? (1 = Sim | 0 = Não)"<<endl;
        cin>>addVert;

        if(addVert)
        {
            cin.sync();
            cout<<endl<<"Digite os novos vértices para serem adicionados (Ex: 1 2): (Não redigite os antigos)"<<endl;
            getline(cin, linha);
            LinhaParaVetor(linha, vertices);

            matriz.resize(vertices.size());
            for( auto &linha : matriz )
                linha.resize(vertices.size());
        }

        cout<<endl<<"Deseja remover vertices? (1 = Sim | 0 = Não)"<<endl;
        cin>>removerVert;

        if(removerVert)
        {
            cin.sync();
            cout<<endl<<"Digite os vértices para serem removidos (Ex: 1 2): "<<endl;
            getline(cin, linha);
            LinhaParaVetor(linha, deletVert);

            for(uint32_t i = 0; i<deletVert.size();i++)
                for(uint32_t j = 0; j<vertices.size();j++)
                    if(deletVert[i]==vertices[j])
                        vertices.erase(vertices.begin()+j);

            matriz.resize(vertices.size());

            for( auto &linha : matriz )
                linha.resize(vertices.size());

            PopulaMatriz(matriz,dirigida,vertices,liga, peso);
        }

        cout<<endl<<"Deseja adicionar arestas/ arcos? (1 = Sim | 0 = Não)"<<endl;
        cin>>addLiga;

        if(addLiga)
        {
            cin.sync();
            cout<<endl<<"Digite arestas/ arcos para serem adicionados (Ex: 1 2 P, sendo P o valor do peso): (Não redigite os antigos)"<<endl;
            getline(cin, linha);
            LinhaParaVetor(linha, liga);
            PopulaMatriz(matriz,dirigida,vertices,liga, peso);
        }

        cout<<endl<<"Deseja remover arestas/ arcos?? (1 = Sim | 0 = Não)"<<endl;
        cin>>removerLiga;

        if(removerLiga)
        {
            cin.sync();
            cout<<endl<<"Digite arestas/ arcos para serem removidas (Ex: 1 2): "<<endl;
            getline(cin, linha);

            LinhaParaVetor(linha, deletLiga);

            for(uint32_t i = 0; i<deletLiga.size();i++)
                for(uint32_t j = 0; j<liga.size();j++)
                    if(deletLiga[i]==liga[j] && deletLiga[i+1]==liga[j+1])
                    {
                        liga.erase(liga.begin()+j);
                        liga.erase(liga.begin()+j+1);
                        liga.erase(liga.begin()+j+2);
                    }

            PopulaMatriz(matriz,dirigida,vertices,liga, peso);
        }

        cout<<endl<<"Deseja fazer busca? (1 = Sim | 0 = Não)"<<endl;
        cin>>busca;

        cout<<endl<<"Deseja visualizar conectividade? (1 = Sim | 0 = Não)"<<endl;
        cin>>conect;

        cout<<endl<<"Deseja visualizar menor caminho a partir de um vértice? (1 = Sim | 0 = Não)"<<endl;
        cin>>dijkstra;

        if(conect)
        {
            cin.sync();
            cout<<"Digite o vertice de inicio da busca:"<<endl;
            cin>>vetInicial;
            cout<<endl;
        }
        sair = 0;

        if(dijkstra)
        {
            cin.sync();
            cout<<"Digite o vertice de inicio da busca:"<<endl;
            cin>>vetInicial;
            cout<<endl;
        }

        vertItersec.resize(0,0);
        for(uint32_t j = 0; j<matriz.size(); j++)
            vertItersec.push_back(0);

        visitados.resize(0,0);
        visitados.resize(matriz.size());
        system("cls");
    }
    return 0;
}
