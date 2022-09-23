#include <iostream>

using namespace std;

struct MEMORY {
    int tag;
    bool dirt=false;
    int last=0;
    int *word;

    void words(int w){
        word = new int[w];
    }
};

bool hit (MEMORY* me, int li, int co, int addr){
    for (int j=0; j<co; j++){
        if (me[li].word[j]==addr){
            return true;
        }
    }
    return false;
}

void lfu(MEMORY* me, int li, int co, int addr){
    int la = me[li].last;
    me[li].word[la]=addr;
    if (me[li].last!=co-1){
        me[li].last++;
    } else {
        me[li].last=0;
    }
}

bool direta (MEMORY* me, int addr, int block, int word=1){
    int p = addr%(block/word);
    if (hit(me, p, word, addr)){
        return true;
    }

    lfu(me, p, word, addr);
    return false;


}

void imprime (MEMORY* me, int li, int co){
    for (int i=0;i<li;i++){
            cout<<i<<": ";
        for (int j=0;j<co;j++){
            cout<<me[i].word[j]<<" ";

        }
        cout<<"\n";
    }
}

int main()
{
    int block, word, li, co, addr, hit=0, miss=0;
    int entrada[16]={1,4,8,5,20,17,19,56,9,11,4,43,5,6,9,17};
    MEMORY* me;
    cout << "informe o número de blocos e o número de palavras: ";
    cin >> block >> word;
    li = block/word;
    co = word;
    me = new MEMORY[li];
    for (int i=0; i<li; i++){
        me[i].words(co);
    }

    for (int i=0; i<16; i++){
        if (direta(me, entrada[i], block, word) ) {
            hit++;
        } else {
            miss++;
        }
    }

    imprime(me, block/word, word);

    cout<<"\n\n Acerto: "<<hit<<", Erro: "<<miss;
    return 0;
}
