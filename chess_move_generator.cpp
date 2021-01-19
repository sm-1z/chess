#include "chess_move_generator.h"

Chess_move_generator::Chess_move_generator(QWidget *parent) : QWidget(parent)
{

}

void Chess_move_generator::AddMove(int from_x, int from_y, int to_x, int to_y, int gen)
{
    if(gen == this->gengerate)
    {
        int i = this->now;
        this->m_MoveList[gen][i] = from_x;
        this->m_MoveList[gen][i+1] = from_y;
        this->m_MoveList[gen][i+2] = to_x;
        this->m_MoveList[gen][i+3] = to_y;
        this->now = this->now + 4;
    }
    else {
        this->gengerate = gen;
        this->now = 0;
        int i = this->now;
        this->m_MoveList[gen][i] = from_x;
        this->m_MoveList[gen][i+1] = from_y;
        this->m_MoveList[gen][i+2] = to_x;
        this->m_MoveList[gen][i+3] = to_y;
        this->now = this->now + 4;
    }
}
void Chess_move_generator::GetRelatePiece(int gen)
{
    int x,y;
    for (x = 1; x < 11 ;x++) {
        for (y = 1 ;y < 10; y++) {
            if(number[x][y] == NOCHESS)
                continue;
            else{
                int heng,shu;
                for (heng = 1 ; heng < 11; heng++) {
                    for (shu = 1;shu <10;shu++) {
                        if(Chessvariate::ISCanMove(x,y,heng,shu))
                            AddMove(x,y,heng,shu,gen);
                    }
                }
                }

        }
    }
}

