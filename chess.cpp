#include <iostream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype> 
#include <vector>
#include <algorithm>
int whitekingpos[2]={7,4};
int blackkingpos[2]={0,4};
bool isincheck=false;
void BoardPrint(char board[8][8]){
    std::cout<<"  a b c d e f g h\n";
    for(int i=0;i<8;i++){
        std::cout<<8-i<< " ";
        for(int j=0;j<8;j++){
            std::cout<<board[i][j]<<" ";
        }
        std::cout<<8-i<<"\n";
    }
    std::cout<<"  a b c d e f g h\n";
}
bool isValidKingMove(char board[8][8], int RowStart, int ColStart, int RowEnd, int ColEnd, char piece){
    char target = board[RowEnd][ColEnd];
 
    if (target != '.' && ((piece >= 'A' && piece <= 'Z' && target >= 'A' && target <= 'Z') || (piece >= 'a' && piece <= 'z' && target >= 'a' && target <= 'z'))) {
        return false;
    }
    int colDiff = abs(ColEnd - ColStart);
    int rowDiff = abs(RowEnd - RowStart);
    if((RowStart==RowEnd && colDiff==1) || (ColStart==ColEnd && rowDiff==1) || (colDiff==1 && rowDiff==1)){
        return true;
    }
    return false;
}
bool isValidPawnMove(char board[8][8],int RowStart, int ColStart,int  RowEnd,int  ColEnd,char piece){
    int direction = (piece == 'P') ? -1 : 1;
 
    if(ColEnd == ColStart && RowEnd == RowStart + direction && board[RowEnd][ColEnd] == '.'){
        return true;
    }
 
    int startRow = (piece == 'P') ? 6 : 1;
    if(ColEnd == ColStart && RowStart == startRow && RowEnd == RowStart + (2 * direction) &&
       board[RowStart + direction][ColStart] == '.' && board[RowEnd][ColEnd] == '.'){
        return true;
    }
    if(RowStart + direction == RowEnd && (ColEnd == ColStart + 1 || ColEnd == ColStart - 1) &&
       board[RowEnd][ColEnd] != '.' && ((piece == 'P' && islower(board[RowEnd][ColEnd])) || (piece == 'p' && isupper(board[RowEnd][ColEnd])))){
        return true;
    }
    return false;
}
bool isValidKnightMove(char board[8][8], int RowStart, int ColStart, int RowEnd, int ColEnd, char piece){
    char target = board[RowEnd][ColEnd];
 
    if (target != '.' && ((piece >= 'A' && piece <= 'Z' && target >= 'A' && target <= 'Z') || (piece >= 'a' && piece <= 'z' && target >= 'a' && target <= 'z'))) {
        return false;
    }
 
    int colDiff = abs(ColEnd - ColStart);
    int rowDiff = abs(RowEnd - RowStart);
 
    if ((colDiff == 2 && rowDiff == 1) || (colDiff == 1 && rowDiff == 2)) {
        return true;
    }
 
    return false;
}
bool isValidBishopMove(char board[8][8], int RowStart, int ColStart, int RowEnd, int ColEnd, char piece){
    char target = board[RowEnd][ColEnd];
 
    if (target != '.' && ((piece >= 'A' && piece <= 'Z' && target >= 'A' && target <= 'Z') || (piece >= 'a' && piece <= 'z' && target >= 'a' && target <= 'z'))) {
        return false;
    }
    if(ColEnd<ColStart && RowEnd<RowStart){
        for(int i=1;i<abs(ColEnd-ColStart);i++){
            if(board[RowStart-i][ColStart-i]!='.'){
                return false;
            }
        }
    }
    else if(ColEnd>ColStart && RowEnd>RowStart){
        for(int i=1;i<abs(ColEnd-ColStart);i++){
            if(board[RowStart+i][ColStart+i]!='.'){
                return false;
            }
        }
    }
    else if(ColEnd<ColStart && RowEnd>RowStart){
        for(int i=1;i<abs(ColEnd-ColStart);i++){
            if(board[RowStart+i][ColStart-i]!='.'){
                return false;
            }
        }
    }
    else if(ColEnd>ColStart && RowEnd<RowStart){
        for(int i=1;i<abs(ColEnd-ColStart);i++){
            if(board[RowStart-i][ColStart+i]!='.'){
                return false;
            }
        }
    }
    int colDiff = abs(ColEnd - ColStart);
    int rowDiff = abs(RowEnd - RowStart);
    if (colDiff==rowDiff) {
        return true;
    }
 
    return false;
}
bool isValidRookMove(char board[8][8], int RowStart, int ColStart, int RowEnd, int ColEnd, char piece){
    if (RowStart == RowEnd && ColStart == ColEnd) return false;
 
    if (RowStart != RowEnd && ColStart != ColEnd) return false;
 
    char target = board[RowEnd][ColEnd];
    if (target != '.' && ((piece >= 'A' && piece <= 'Z' && target >= 'A' && target <= 'Z') || (piece >= 'a' && piece <= 'z' && target >= 'a' && target <= 'z'))) {
        return false;
    }
 
    if (RowStart == RowEnd) {
        int step = (ColEnd > ColStart) ? 1 : -1;
        for (int c = ColStart + step; c != ColEnd; c += step) {
            if (board[RowStart][c] != '.') return false;
        }
    } else {
        int step = (RowEnd > RowStart) ? 1 : -1;
        for (int r = RowStart + step; r != RowEnd; r += step) {
            if (board[r][ColStart] != '.') return false;
        }
    }
 
    return true;
}
bool isValidQueenMove(char board[8][8], int RowStart, int ColStart, int RowEnd, int ColEnd, char piece){
    return isValidRookMove(board, RowStart, ColStart, RowEnd, ColEnd, piece) || 
           isValidBishopMove(board, RowStart, ColStart, RowEnd, ColEnd, piece);
}
 
bool isInCheck(char board[8][8], int kingRow, int kingCol){
    bool checkingWhite = isupper(board[kingRow][kingCol]);
 
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            char piece = board[row][col];
            if(piece == '.') continue;
 
            bool isEnemy = checkingWhite ? islower(piece) : isupper(piece);
            if(!isEnemy) continue;
 
            switch(tolower(piece)){
                case 'p': if(isValidPawnMove(board, row, col, kingRow, kingCol, piece))   return true; break;
                case 'r': if(isValidRookMove(board, row, col, kingRow, kingCol, piece))   return true; break;
                case 'n': if(isValidKnightMove(board, row, col, kingRow, kingCol, piece)) return true; break;
                case 'b': if(isValidBishopMove(board, row, col, kingRow, kingCol, piece)) return true; break;
                case 'q': if(isValidQueenMove(board, row, col, kingRow, kingCol, piece))  return true; break;
                case 'k': if(isValidKingMove(board, row, col, kingRow, kingCol, piece))   return true; break;
            }
        }
    }
    return false;
}
bool validTurn(char board[8][8], int RowStart, int ColStart, int RowEnd, int ColEnd, const int &counter){
    if(isupper(board[RowStart][ColStart])&& counter%2==0)return true;
    if(isupper(board[RowStart][ColStart])&& counter%2!=0)return false;
    if(islower(board[RowStart][ColStart])&& counter%2!=0)return true;
    if(islower(board[RowStart][ColStart])&& counter%2==0)return false;
    return false;
}
bool whiteKingMoved=false, blackKingMoved=false;
bool whiteRookHMoved=false, whiteRookAMoved=false; 
bool blackRookHMoved=false, blackRookAMoved=false;
bool kingSafeAt(char board[8][8], int row, int col, char king){
    char saved = board[row][col];
    board[row][col] = king;
    bool safe = !isInCheck(board, row, col);
    board[row][col] = saved;
    return safe;
}
bool isValidCastle(char board[8][8], const std::string &move, int RowStart, int ColStart, int RowEnd, int ColEnd, const int &counter){
    if(move=="O.O" && counter%2==0){
        if(!whiteKingMoved && !whiteRookHMoved && board[7][4]=='K' && board[7][7]=='R' &&
           board[7][5]=='.' && board[7][6]=='.' &&
           kingSafeAt(board,7,4,'K') && kingSafeAt(board,7,5,'K') && kingSafeAt(board,7,6,'K')){
            return true;
        }
    }
    if(move=="O.O.O" && counter%2==0){
        if(!whiteKingMoved && !whiteRookAMoved && board[7][4]=='K' && board[7][0]=='R' &&
           board[7][1]=='.' && board[7][2]=='.' && board[7][3]=='.' &&
           kingSafeAt(board,7,4,'K') && kingSafeAt(board,7,3,'K') && kingSafeAt(board,7,2,'K')){
            return true;
        }
    }
    if(move=="O.O" && counter%2!=0){
        if(!blackKingMoved && !blackRookHMoved && board[0][4]=='k' && board[0][7]=='r' &&
           board[0][5]=='.' && board[0][6]=='.' &&
           kingSafeAt(board,0,4,'k') && kingSafeAt(board,0,5,'k') && kingSafeAt(board,0,6,'k')){
            return true;
        }
    }
    if(move=="O.O.O" && counter%2!=0){
        if(!blackKingMoved && !blackRookAMoved && board[0][4]=='k' && board[0][0]=='r' &&
           board[0][1]=='.' && board[0][2]=='.' && board[0][3]=='.' &&
           kingSafeAt(board,0,4,'k') && kingSafeAt(board,0,3,'k') && kingSafeAt(board,0,2,'k')){
            return true;
        }
    }
    return false;
}
bool isValidMove(char board[8][8], int RowStart, int ColStart, int RowEnd, int ColEnd, const int &counter, const std::string &move){
    if(move=="O.O" || move=="O.O.O") return isValidCastle(board, move, RowStart, ColStart, RowEnd, ColEnd, counter);
    char piece = board[RowStart][ColStart];
    if(piece=='.')return false;
    if(piece=='p'|| piece=='P' ){
        if((isValidPawnMove(board, RowStart, ColStart, RowEnd, ColEnd, piece))&& (validTurn(board, RowStart, ColStart, RowEnd, ColEnd, counter))){
            return true;
        }else{
            return false;
        }
    }
    if(piece=='r' || piece=='R' ){
        if((isValidRookMove(board, RowStart, ColStart, RowEnd, ColEnd, piece))&& (validTurn(board, RowStart, ColStart, RowEnd, ColEnd, counter))){
            return true;
        }else{
            return false;
        }
    }
    if(piece=='n' || piece=='N' ){
        if((isValidKnightMove(board, RowStart, ColStart, RowEnd, ColEnd, piece))&& (validTurn(board, RowStart, ColStart, RowEnd, ColEnd, counter))){
            return true;
        }else{
            return false;
        }
    }
    if(piece=='b' || piece=='B' ){
        if((isValidBishopMove(board, RowStart, ColStart, RowEnd, ColEnd, piece))&& (validTurn(board, RowStart, ColStart, RowEnd, ColEnd, counter))){
            return true;
        }else{
            return false;
        }
    }
    if(piece=='q' || piece=='Q' ){
        if((isValidQueenMove(board, RowStart, ColStart, RowEnd, ColEnd, piece))&& (validTurn(board, RowStart, ColStart, RowEnd, ColEnd, counter))){
            return true;
        }else{
            return false;
        }
    }
    if(piece=='k' || piece=='K' ){
        if((isValidKingMove(board, RowStart, ColStart, RowEnd, ColEnd, piece))&& (validTurn(board, RowStart, ColStart, RowEnd, ColEnd, counter))){
            return true;
        }else{
            return false;
        }
    }
    return false;
}
struct Move {
    int RowStart;
    int ColStart;
    int RowEnd;
    int ColEnd;
};
std::vector <Move> getAllPossibleMoves(char board[8][8], int RowStart, int ColStart, const int &counter){
    std::vector <Move> moves;
    for(RowStart=0;RowStart<8;RowStart++){
        for(ColStart=0;ColStart<8;ColStart++){       
            for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                    if(isValidMove(board, RowStart, ColStart, i, j, counter, "")){
                        Move m;
                        m.RowStart = RowStart;
                        m.ColStart = ColStart;
                        m.RowEnd = i;
                        m.ColEnd = j;
                        moves.push_back(m);
                    }
                }       
            }
        } 
    }  
    return moves;
}

bool Checkmate(char board[8][8], int RowStart, int ColStart, const int &counter){
    std::vector <Move> moves=getAllPossibleMoves(board, RowStart, ColStart, counter);
    std::vector <Move> validMoves;
    for(int i=0;i<moves.size();i++){
        Move m=moves[i];
        char moved= board[m.RowStart][m.ColStart];
        char captured = board[m.RowEnd][m.ColEnd];
        board[m.RowEnd][m.ColEnd] = moved;
        board[m.RowStart][m.ColStart] = '.';
        int kingRow = RowStart;
        int kingCol = ColStart;
        if(moved == 'K' || moved == 'k'){
            kingRow = m.RowEnd;
            kingCol = m.ColEnd;
        }

        if(!isInCheck(board, kingRow, kingCol)){
            validMoves.push_back(m);
            board[m.RowStart][m.ColStart] = moved;
            board[m.RowEnd][m.ColEnd] = captured;
        }
        else {
            board[m.RowStart][m.ColStart] = moved;
            board[m.RowEnd][m.ColEnd] = captured;
        }
    }
    return validMoves.empty();
}
int main(){
    char board[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };
    int counter=0;
    bool whiteTurn = true;
    while(true){
        BoardPrint(board);
        std::string move;
        std::cout << (counter%2==0? "White's turn: " : "Black's turn: ");
        std::cin >> move;
        if(move.length()!=4 && move != "O.O" && move != "O.O.O"){
            std::cout<<"Invalid move format. Please use format like e2e4 or O.O/O.O.O for castle.\n";
            continue;
        }
        if(move.length() == 4 && (move[0] < 'a' || move[0] > 'h' || move[1] < '1' || move[1] > '8' ||
           move[2] < 'a' || move[2] > 'h' || move[3] < '1' || move[3] > '8')){
            std::cout<<"Invalid move format. Squares must be a-h and 1-8.\n";
            continue;
        }
        int ColStart=0, RowStart=0, ColEnd=0, RowEnd=0;
            if(move=="O.O" || move=="O.O.O"){
                int row = (counter%2==0) ? 7 : 0;
                RowStart = row; ColStart = 4; RowEnd = row;
                ColEnd = (move=="O.O") ? 6 : 2;
            }else{
                ColStart = move[0] - 'a';
                RowStart = 8 - (move[1] - '0');
                ColEnd = move[2] - 'a';
                RowEnd = 8 - (move[3] - '0');
            }     
        if(isValidMove(board, RowStart, ColStart, RowEnd, ColEnd, counter, move)){
            char moved = board[RowStart][ColStart];
            char captured = board[RowEnd][ColEnd];
            board[RowEnd][ColEnd] = moved;
            board[RowStart][ColStart] = '.';
            bool whiteMoved = isupper(moved);
            int kingRow = whiteMoved ? whitekingpos[0] : blackkingpos[0];
            int kingCol = whiteMoved ? whitekingpos[1] : blackkingpos[1];              
            if(moved == 'K' || moved == 'k'){
                kingRow = RowEnd;
                kingCol = ColEnd;
            }      
            if(isInCheck(board, kingRow, kingCol)){
                board[RowStart][ColStart] = moved;
                board[RowEnd][ColEnd] = captured;
                std::cout << "That leaves your king in check.\n";
            } else {
                if(moved == 'K'){ whitekingpos[0] = RowEnd; whitekingpos[1] = ColEnd; }
                if(moved == 'k'){ blackkingpos[0] = RowEnd; blackkingpos[1] = ColEnd; }
                if(moved=='K') whiteKingMoved=true;
                if(moved=='k') blackKingMoved=true;
                if(moved=='R' && RowStart==7 && ColStart==7) whiteRookHMoved=true;
                if(moved=='R' && RowStart==7 && ColStart==0) whiteRookAMoved=true;
                if(moved=='r' && RowStart==0 && ColStart==7) blackRookHMoved=true;
                if(moved=='r' && RowStart==0 && ColStart==0) blackRookAMoved=true;
                if(move=="O.O"){   board[RowStart][5]=board[RowStart][7]; board[RowStart][7]='.'; }
                if(move=="O.O.O"){ board[RowStart][3]=board[RowStart][0]; board[RowStart][0]='.'; }
                counter++;
                int enemyKingRow = whiteMoved ? blackkingpos[0] : whitekingpos[0];
                int enemyKingCol = whiteMoved ? blackkingpos[1] : whitekingpos[1];
                if(isInCheck(board, enemyKingRow, enemyKingCol)){
                    std::cout << (whiteMoved ? "Black is in check.\n" : "White is in check.\n");
                    if (Checkmate(board, enemyKingRow, enemyKingCol, counter)) {
                        std::cout << (whiteMoved ? "Checkmate! White wins.\n" : "Checkmate! Black wins.\n");
                        break;
                    } else {
                        std::cout << "";
                    }
                }
                else if(Checkmate(board, enemyKingRow, enemyKingCol, counter)){
                std::cout<<"Stalemate, draw.\n";
                break;
            }
            }
        }
        else{
            std::cout<<"Invalid move. Try again.\n";
        }
    }
    BoardPrint(board);
    return 0;
}
