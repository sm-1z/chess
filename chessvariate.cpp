#include "chessvariate.h"

int number[11][10] = {{90, -1, -2, -3, -4, -5, -6, -7, -8, -9},
                      {-1, G_CAR, G_HORSE, G_ELEPHANT, G_BISHOP, G_KING, G_BISHOP, G_ELEPHANT, G_HORSE, G_CAR},
                      {-2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {-3, 0, G_CANON, 0, 0, 0, 0, 0, G_CANON, 0},
                      {-4, G_PAWN, 0, G_PAWN, 0, G_PAWN, 0, G_PAWN, 0, G_PAWN},
                      {-5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {-6, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {-7, R_PAWN, 0, R_PAWN, 0, R_PAWN, 0, R_PAWN, 0, R_PAWN},
                      {-8, 0, R_CANON, 0, 0, 0, 0, 0, R_CANON, 0},
                      {-9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {-10, R_CAR, R_HORSE, R_ELEPHANT, R_BISHOP, R_KING, R_BISHOP, R_ELEPHANT, R_HORSE, R_CAR},
                     };

Chessvariate::Chessvariate(QWidget *parent) : QWidget(parent)
{

}

bool Chessvariate::ISValidMove(int From_heng,int From_shu, int To_heng, int To_shu){
    int nMoveChessID = number[From_heng][From_shu];
    int nTargeID = number[To_heng][To_shu];
    if(IsSameSide(nMoveChessID, nTargeID)){
        qDebug() << "两子同阵营";
        return false;
    }
    else{
        return ISCanMove(From_heng, From_shu, To_heng, To_shu);
    }
}

void Chessvariate::pictureID_to_ChessID(int x)
{
    switch (x) {
    case 0:
    case 8:
        x = R_CAR;
        break;
    case 1:
    case 7:
        x = R_HORSE;
        break;
    case 2:
    case 6:
        x = R_ELEPHANT;
        break;
    case 3:
    case 5:
        x = R_BISHOP;
        break;
    case 4:
        x = R_KING;
        break;
    case 9:
    case 10:
        x = R_CANON;
        break;
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        x = R_PAWN;
        break;
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
        x = G_PAWN;
        break;
    case 21:
    case 22:
        x = G_CANON;
        break;
    case 23:
    case 31:
        x = G_CAR;
        break;
    case 24:
    case 30:
        x = G_HORSE;
        break;
    case 25:
    case 29:
        x = G_ELEPHANT;
        break;
    case 26:
    case 28:
        x = G_BISHOP;
        break;
    case 27:
        x = G_KING;
        break;
    default:
        break;
    }
}

bool Chessvariate::ISCanMove(int From_heng,int From_shu, int To_heng, int To_shu)
{
    if(From_heng == To_heng && From_shu == To_shu){
        qDebug() << "两次位置相同";
        return false;
    }
    int i=0,j=0;
    int count = -1;
    switch (number[From_heng][From_shu]) {
    case R_CAR:
    case G_CAR:
        if (From_heng == To_heng || From_shu == To_shu)
        {
            if(From_shu == To_shu)
            {
                if(From_heng < To_heng){
                    i = From_heng+1;
                    j = To_heng;
                }
                else{
                    i = To_heng+1;
                    j = From_heng;
                }
                for (;i<j;i++) {
                    if(number[i][From_shu] == NOCHESS)
                        continue;
                    else
                        return false;
                }
                return true;
            }
            else{
                if(From_shu < To_shu){
                    i = From_shu+1;
                    j = To_shu;
                }
                else {
                    i = To_shu+1;
                    j = From_shu;
                }
                for (;i<j;i++) {
                    if(number[From_heng][i] == NOCHESS)
                        continue;
                    else
                        return false;
                }
                return true;
            }

        }
        else
            return false;
        break;
    case R_HORSE:
    case G_HORSE:
        if(abs((From_heng - To_heng)*(From_shu - To_shu)) == 2){
            if(abs(From_heng - To_heng) == 2){
                if(number[(From_heng + To_heng)/2][From_shu] == NOCHESS)
                    return true;
                else
                    return false;
            }
            else{
                if(number[From_heng][(From_shu + To_shu)/2] == NOCHESS)
                    return true;
                else
                    return false;
            }
        }
        else
            return false;
        break;
    case R_ELEPHANT:
    case G_ELEPHANT:
        if(abs(From_heng - To_heng) == 2 && abs(From_shu - To_shu) == 2){
            if((From_heng -5.5) * (To_heng - 5.5 ) > 0){
                if(number[(From_heng + To_heng)/2][(From_shu + To_shu)/2] == NOCHESS)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
        break;
    case R_CANON:
    case G_CANON:
        if(From_heng == To_heng || From_shu == To_shu){
            if(From_shu == To_shu)
            {
                if(From_heng < To_heng){
                    i = From_heng;
                    j = To_heng;
                }
                else{
                    i = To_heng;
                    j = From_heng;
                }
                for (;i<j;i++) {
                    if(number[i][From_shu] != NOCHESS)
                        count++;
                }
                if(count > 1){
                    qDebug() << "两者棋子数大于1";
                    return false;
                }
                else if(count == 1 && number[To_heng][To_shu] == NOCHESS){
                    qDebug() << "目标无敌方棋子，无法攻击";
                    return false;
                }
                else if (count == 0 && number[To_heng][To_shu] != NOCHESS) {
                    qDebug() << "无炮架，无法攻击";
                    return false;
                }
                else{
                    return true;
                }
            }
            else{
                if(From_shu < To_shu){
                    i = From_shu;
                    j = To_shu;
                }
                else {
                    i = To_shu;
                    j = From_shu;
                }
                for (;i<j;i++) {
                    if(number[From_heng][i] != NOCHESS)
                        count++;
                }
                if(count > 1){
                    qDebug() << "两者棋子数大于1";
                    return false;
                }
                else if(count == 1 && number[To_heng][To_shu] == NOCHESS){
                    qDebug() << From_heng << From_shu << To_heng << To_shu << count;
                    qDebug() << "目标无敌方棋子，无法攻击";
                    return false;
                }
                else if (count == 0 && number[To_heng][To_shu] != NOCHESS) {
                    qDebug() << "无炮架，无法攻击";
                    return false;
                }
                else{
                    return true;
                }
            }
        }
        else
            return false;
        break;
    case R_BISHOP:
        if(From_heng < 8 || From_shu < 4 || From_shu > 6 || To_heng < 8 || To_shu < 4 || To_shu > 6)
            return false;
        else{
            if(abs(From_shu - To_shu) == 1 && abs(From_heng - To_heng) == 1)
                return  true;
            else
                return false;
        }
        break;
    case G_BISHOP:
        if(From_heng > 3 || From_shu < 4 || From_shu > 6 || To_heng > 3 || To_shu < 4 || To_shu > 6)
            return false;
        else{
            if(abs(From_shu - To_shu) == 1 && abs(From_heng - To_heng) == 1)
                return  true;
            else
                return false;
        }
        break;
    case R_PAWN:
        qDebug() << "红兵";
        if(From_heng >= To_heng){
            if(From_heng > 5 && abs(From_shu -To_shu) == 1){
                qDebug() << From_heng << From_shu << To_heng << To_shu;
                return false;
            }
            else{
               if(abs(From_shu-To_shu) + abs(From_heng-To_heng) == 1)
                   return true;
               else{
                   qDebug() << "走格数大于1";
                   return false;
               }
            }
        }
        else{
            qDebug() << "后退";
            return false;
        }
        break;
    case G_PAWN:
        if(From_heng <= To_heng){
            if(From_heng < 6 && abs(From_shu -To_shu) == 1){
                return false;
            }
            else{
               if(abs(From_shu-To_shu) + abs(From_heng-To_heng) == 1)
                   return true;
               else
                   return false;
            }
        }
        else
            return false;
        break;
    case R_KING:
        if(number[To_heng][To_shu] == G_KING){
            if(From_shu == To_shu){
                for (i = From_heng-1;i>To_heng;i--) {
                    if(number[i][From_shu] == NOCHESS)
                        continue;
                    else {
                        return false;
                    }
                }
                return true;
            }
            else
                return false;
        }
        else {
            if(To_heng < 8 || To_shu < 4 || To_shu > 6)
                return false;
            else {
                if(abs(From_shu-To_shu) + abs(From_heng-To_heng) == 1)
                    return  true;
                else
                    return false;
            }
        }
        break;
    case G_KING:
        if(number[To_heng][To_shu] == R_KING){
            if(From_shu == To_shu){
                for (i = From_heng+1;i<To_heng;i++) {
                    if(number[i][From_shu] == NOCHESS)
                        continue;
                    else {
                        return false;
                    }
                }
                return true;
            }
            else
                return false;
        }
        else {
            if(To_heng > 3 || To_shu < 4 || To_shu > 6)
                return false;
            else {
                if(abs(From_shu-To_shu) + abs(From_heng-To_heng) == 1)
                    return  true;
                else
                    return false;
            }
        }
        break;
    default:
        return false;
        break;
    }
}




