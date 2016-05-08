#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
using namespace std;

class Tree
{
	public:
	 int qwe;
	 char c;
	 Tree *left, *right;

	 Tree(){left=right=NULL;}

	 Tree(Tree *L, Tree *R)
	 {  left =  L;
	    right = R;
	    qwe = L->qwe + R->qwe;  }
};


struct Scor
{
    bool operator()(const Tree* l, const Tree* r) const { return l->qwe < r->qwe; }
};


vector<bool> code;
map<char,vector<bool> > table;

void Create(Tree *korin)
{
    if (korin->left!=NULL)
                      { code.push_back(0);
                      Create(korin->left);}

    if (korin->right!=NULL)
                       { code.push_back(1);
                       Create(korin->right);}

    if (korin->left==NULL && korin->right==NULL) table[korin->c]=code;

    code.pop_back();
}


int main (int argc, char *argv[])
{
	ifstream FileInput("input.txt", ios::out | ios::binary);

	map<char,int> amas;

	while (!FileInput.eof())
	{ char c = FileInput.get();
	   amas[c]++;}



   list<Tree*> t;
   for( map<char,int>::iterator itr=amas.begin(); itr!=amas.end(); ++itr)
   {
      Tree *p = new Tree;
      p->c = itr->first;
      p->qwe = itr->second;
      t.push_back(p);      }



  while (t.size()!=1)
  {
     t.sort(Scor());

     Tree *SonL = t.front();
     t.pop_front();
     Tree *SonR = t.front();
     t.pop_front();

     Tree *parent = new Tree(SonL,SonR);
     t.push_back(parent);

  }

	Tree *korin = t.front();


   	Create(korin);

              map<char, vector<bool> >::iterator it;
         vector<bool>::iterator ii;
         for (it = table.begin(); it != table.end(); it++)
         {
          cout << it->first << " : ";
          for (ii = table[it->first].begin(); ii != table[it->first].end(); ii++)
           cout << (*ii);
          cout << "\n";
         }

    FileInput.clear(); FileInput.seekg(0);

	ofstream g("output.txt", ios::out | ios::binary);

    int k=0; char e=0;
    while (!FileInput.eof())
    { char c = FileInput.get();
	  vector<bool> x = table[c];
	  for(int n=0; n<x.size(); n++)
	   {
        e = e | x[n]<<(7-k);
	    k++;
	    if (k==8) { k=0;   g<<e; e=0; }
       }
    }

    FileInput.close();
	g.close();



}
