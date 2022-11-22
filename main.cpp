/* Joao Luís Chiarelotto Crema
ENUNCIADO

Sua tarefa será construir uma hash table usando como estrutura base uma árvore
heap que use como índice o resultado de uma função de hash disponível na
internet. Esta hash Table deve ser capaz de armazenar senhas (strings) com no
mínimo 10 caracteres e no máximo 50 caracteres. No seu trabalho, como
comentário, deve constar a referência para a função de hash escolhida para a
criação do índice da árvore heap. Você deverá criar, no mínimo, uma função de
inclusão, exclusão, e busca. A função de inclusão deve retornar Falso, sempre
que o elemento a ser inserido já exista na tabela.

referencia para hash function: https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus
(com algumas alteracoes)

*/

#include <iostream>
#include <random>
#include <string>
using namespace std;

class ItemHash 
{
public:
  int key;
  string senha;
};

class HashTable 
{
private:
  int n; // N de itens na tabela
  ItemHash *senhas;

public:
  HashTable(int n);
  int Index(int key);
  bool Confere(int ind);
  bool ProcuraSenha(string str);
  void Insere(string str, int k);
  bool Remove(int index);
  void Imprime();
  ~HashTable();
};

HashTable::HashTable(int n) 
{
  this->n = n;
  ItemHash lista[n];
  for (int i = 0; i < n; i++) 
  {
    lista[i].senha = "";
    lista[i].key = 0;
  }
  senhas = lista;
}

int HashTable::Index(int key) 
{
  int x = key % n;
  return x;
}

bool HashTable::Confere(int ind) 
{ //false = index ocupado, true = index liberado 
  for (int i = 0; i < n; i++) 
  {     
    if (senhas[i].senha == "") 
    {
      return true;
    }
  }
  return false;
}

bool HashTable::ProcuraSenha(string str) 
{ // true = senha encontrada
  for (int i = 0; i < n; i++) 
  {
    if (senhas[i].senha == str) 
    {
      return true;
    }
  }
  return false;
}

void HashTable::Insere(string str, int k) 
{
  int x = Index(k);
  if (!ProcuraSenha(str)) 
  {
    while (!Confere(x)) 
    {
      x++;
    }
    senhas[x].senha = str;
    senhas[x].key = k;
  }
}

bool HashTable::Remove(int index) 
{
  if (senhas[index].senha != "") 
  {
    senhas[index].senha = "";
    senhas[index].key = 0;
    return true;
  }
  return false;
}

void HashTable::Imprime() 
{
  cout << '{' << endl;
  for (int i = 0; i < n; i++) 
  {
    if (i>=10)
    {
      if (senhas[i].senha == "") 
      {
        cout << i << ": [Vazio]" << endl;
      } else 
      {
        cout << i << ": [" << senhas[i].key << ", " << senhas[i].senha << "]"
             << endl;
      }
    } else 
    {
      if (senhas[i].senha == "") 
      {
        cout << i << ":  [Vazio]" << endl;
      } else 
      {
        cout << i << ":  [" << senhas[i].key << ", " << senhas[i].senha << "]"
             << endl;
      }
    }
  }
  cout << "}\nFim" << endl;
}

HashTable::~HashTable() 
{
  this->n = 0;
  for (int i = 0; i < n; i++) 
  {
    senhas[i].senha = nullptr;
    senhas[i].key = 0;
  }
  cout << "Memoria limpa" << endl;
}

int main() 
{
  int x, y;
  string s = "";
  string teste_busca[2];
  char chars[36] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
                    'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  //twister de mersenne
  random_device a;
  mt19937 gerador(a());
  uniform_int_distribution<int> alfa(0, 35);
  uniform_int_distribution<int> tam(10, 50);
  uniform_int_distribution<int> keys(1, 50);
  HashTable hash(50);
  for (int i = 0; i < 50; i++) 
  {
    x = keys(gerador);
    y = tam(gerador);
    for (int j = 0; j < y; j++) 
    {
      s += chars[alfa(gerador)];
    }
    hash.Insere(s, x);
    if (i >= 48) 
    {
      teste_busca[i - 48] = s;
    }
    s = "";
  }
  cout << "Hash Table: " << endl;
  hash.Imprime();
  for (int i = 0; i < 2; i++) 
  {
    if (hash.ProcuraSenha(teste_busca[i])) 
    {
      cout << "\nResultado da busca" << teste_busca[i] << ": true"
           << endl;
    } else {
      cout << "\nResultado da busca" << teste_busca[i] << ": false"
           << endl;
    }
  }
  for (int i = 0; i < 5; i++) 
  {
    if (hash.Remove(i)) 
    {
      cout << "\nItem do indice " << i << " item removido " << endl;
    } else {
      cout << "\nNenhum item econtrado " << i << endl;
    }
  }
  cout << "\nHash Table remodelada (apos a remocao): " << endl;
  hash.Imprime();
}