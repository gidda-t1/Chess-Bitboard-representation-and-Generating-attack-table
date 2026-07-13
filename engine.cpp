#include <iostream>
#include <bitset>

#define U64 unsigned long long
#define empty_board "8/8/8/8/8/8/8/8 w - - "
#define start_position "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 "
#define tricky_position "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 "
#define killer_position "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define cmk_position "r2q1rk1/ppp2ppp/2n1bn2/2b1p3/3pP3/3P1NPP/PPP1NPB1/R1BQ1RK1 b - - 0 9 "


//board squares through chess notation and pieces
enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1, no_sq
};
const char *square_to_coordinates[] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
};

enum{black,white, both};
enum{bishop, rook};   


// ==================================
 
//           Chess board
 
//  ==================================

//                             WHITE PIECES


//         Pawns                  Knights              Bishops
        
//   8  0 0 0 0 0 0 0 0    8  0 0 0 0 0 0 0 0    8  0 0 0 0 0 0 0 0
//   7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0
//   6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
//   5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
//   4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
//   3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
//   2  1 1 1 1 1 1 1 1    2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0
//   1  0 0 0 0 0 0 0 0    1  0 1 0 0 0 0 1 0    1  0 0 1 0 0 1 0 0

//      a b c d e f g h       a b c d e f g h       a b c d e f g h


//          Rooks                 Queens                 King

//   8  0 0 0 0 0 0 0 0    8  0 0 0 0 0 0 0 0    8  0 0 0 0 0 0 0 0
//   7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0
//   6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
//   5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
//   4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
//   3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
//   2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0
//   1  1 0 0 0 0 0 0 1    1  0 0 0 1 0 0 0 0    1  0 0 0 0 1 0 0 0

//      a b c d e f g h       a b c d e f g h       a b c d e f g h


//                             BLACK PIECES


//         Pawns                  Knights              Bishops
        
//   8  0 0 0 0 0 0 0 0    8  0 1 0 0 0 0 1 0    8  0 0 1 0 0 1 0 0
//   7  1 1 1 1 1 1 1 1    7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0
//   6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
//   5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
//   4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
//   3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
//   2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0
//   1  0 0 0 0 0 0 0 0    1  0 0 0 0 0 0 0 0    1  0 0 0 0 0 0 0 0

//      a b c d e f g h       a b c d e f g h       a b c d e f g h


//          Rooks                 Queens                 King

//   8  1 0 0 0 0 0 0 1    8  0 0 0 1 0 0 0 0    8  0 0 0 0 1 0 0 0
//   7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0
//   6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
//   5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
//   4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
//   3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
//   2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0
//   1  0 0 0 0 0 0 0 0    1  0 0 0 0 0 0 0 0    1  0 0 0 0 0 0 0 0

//      a b c d e f g h       a b c d e f g h       a b c d e f g h



//                              OCCUPANCIES


//      White occupancy       Black occupancy       All occupancies

//   8  0 0 0 0 0 0 0 0    8  1 1 1 1 1 1 1 1    8  1 1 1 1 1 1 1 1
//   7  0 0 0 0 0 0 0 0    7  1 1 1 1 1 1 1 1    7  1 1 1 1 1 1 1 1
//   6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
//   5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
//   4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
//   3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
//   2  1 1 1 1 1 1 1 1    2  0 0 0 0 0 0 0 0    2  1 1 1 1 1 1 1 1
//   1  1 1 1 1 1 1 1 1    1  0 0 0 0 0 0 0 0    1  1 1 1 1 1 1 1 1



//                             ALL TOGETHER

//                         8  ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
//                         7  ♟︎ ♟︎ ♟︎ ♟︎ ♟︎ ♟︎ ♟︎ ♟︎
//                         6  . . . . . . . .
//                         5  . . . . . . . .
//                         4  . . . . . . . .
//                         3  . . . . . . . .
//                         2  ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙
//                         1  ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖

//                            a b c d e f g h
//


//declaring the game variables
U64 bitboards[12]; // 6 for each side
U64 occupancies[3]; // To know about the blockers
int side = -1; // illegal side by default
int castle = 0; // No castle yet
int enpassant_sq = no_sq; // No enpassant yet.

//For castling: 
//              0001 -> white 0-0               1001 -> white 0-0 and black 0-0-0=
//              0010 -> white 0-0-0             1111 -> all type of castling is valid  
//              0100 -> black 0-0
//              1000 -> black 0-0-0

enum {wk = 1, wq = 2 , bk = 4 , bq = 8 }; // castling enum
enum {P,N,B,R,Q,K,p,n,b,r,q,k};
const char ascii_pieces[] = "PNBRQKpnbrqk";
const char *unicode_pieces[] = {"♟︎", "♞", "♝", "♜", "♛", "♚", "♙", "♘", "♗", "♖", "♕", "♔"  };  
int char_pieces[128];

void init_pieces()
{
    for(int i=0;i<128;i++) char_pieces[i] = -1;
    char_pieces['P'] = P,char_pieces['N'] = N,char_pieces['B'] = B;
    char_pieces['R'] = R,char_pieces['Q'] = Q,char_pieces['K'] = K;

    char_pieces['p'] = p,char_pieces['n'] = n,char_pieces['b'] = b;
    char_pieces['r'] = r,char_pieces['q'] = q,char_pieces['k'] = k;
}
 


//edge in the chess board
const U64 not_a_file = 18374403900871474942ULL;
const U64 not_h_file = 9187201950435737471ULL;
const U64 not_eight_rank = 18446744073709551360ULL;
const U64 not_first_rank = 72057594037927935ULL;
const U64 not_ab_file = 18229723555195321596ULL;
const U64 not_gh_file = 4557430888798830399ULL;

// ===================================
//             BITBOARD
// ===================================

//bit functions

// inline copies the exact code written in the braces into the main function where exactly we need it.
// Doesnt have any overhead like function's overhead
// Reduces typing and saves our time
//inline is used for small functions only, because in large functions, copying would increase the space in ram and .exe file in harddrive

inline void set_bit(U64 &bitboard, int sq_number) {bitboard = bitboard | (1ULL<<sq_number); }
inline bool get_bit(U64 bitboard, int sq_number) {return (bitboard & (1ULL<<sq_number)) ? 1 : 0; } 
inline void unset_bit(U64 &bitboard, int sq_number) {bitboard = bitboard &  ~(1ULL<<sq_number);} 
inline int get_ls1b(U64 bitboard) {if (bitboard) return __builtin_ctzll(bitboard);return -1;}
inline int get_all1b(U64 bitboard) {return __builtin_popcountll(bitboard);}
    
// Printing the bitboard
    void print_bitboard(U64 &bitboard)
    {
        std::cout<<"\n";
        for(int rank = 0; rank<8; rank++)
        {
            for(int file = 0; file<8; file++) 
            {
                if(!file) std::cout<<(8-rank)<<"  ";
                int sq_number = rank*8 + file;
                std::cout<< get_bit(bitboard, sq_number)<<" ";
            }
            std::cout<<"\n";
        }
        std::cout<<"   a b c d e f g h\n\n";
        std::cout<<"   Bitboard : "<< bitboard<<"\n\n";
    }

    //Printing the board in unicode style
    void print_board()
    {
        std::cout<<"\n";
        occupancies[white] = 0ULL;
        occupancies[black] = 0ULL;
        occupancies[both]  = 0ULL;
        
        for(int rank = 0; rank<8; rank++)
        {
            for(int file = 0; file<8; file++)
            {
                int piece = -1; // If there is no piece, then print "."
                int square =  rank*8 + file;
                if(!file) std:: cout<<8-rank<<"  ";
                for(int board_piece = P; board_piece<=k; board_piece++)
                {
                    if(get_bit(bitboards[board_piece], square))  
                    {
                        piece = board_piece;
                        break;
                    }
                }
                if(piece == -1) std:: cout<<"  .";
                else std:: cout<<"  "<<unicode_pieces[piece];
            }
            std::cout<<"\n";
        }

        for(int i=P; i<=K; i++) occupancies[white] |= bitboards[i];
        for(int i=p; i<=k; i++) occupancies[black] |= bitboards[i];
        occupancies[both] |= occupancies[white] | occupancies[black];

        std::cout<<"     a  b  c  d  e  f  g  h\n\n";
        std:: cout<<"Side : "<<((side) ? "white" : "black")<<"\n"; 
        std:: cout<<"Enpassant square : "<<((enpassant_sq==no_sq)?"no" : square_to_coordinates[enpassant_sq])<<"\n";
        std:: cout<<"Castling right : " << ((castle & wk)?"wk,":"-,")<<((castle & wq)?"wq,":"-,")<<((castle & bk)?"bk,":"-,")<<((castle & bq)?"bq,":"-,")<<"\n";
        std::cout<<"\n";
    }


// ================================
//         PARSER FEN
// ================================
void parser_fen(const char* fen)
{
    //resetting the bitboards 
    for(int i=0;i<12;i++) bitboards[i] = 0ULL;
    for(int i=0;i<3; i++) occupancies[i] = 0ULL;


    for(int rank = 0; rank<=7; rank++)
    {
        for(int file  = 0;  file<=7; file++)
        {
            int square = rank*8+file;

            if((*fen>='a' && *fen<='z') || (*fen>='A' && *fen<='Z'))
            {
                set_bit(bitboards[char_pieces[*fen]], square);
                fen++;
            }
            else if(*fen>='0' && *fen<='8')
            {
                int offset = *fen - '0'; 
                file += (offset-1);
                fen++;
            }   
            if(*fen=='/') 
            {
                fen++; 
                break;
            }

        }
    }

//Parsing the game variables 
    fen++;
    side = (*fen == 'w' ? 1 : 0);
    fen+=2;

    //castling
    while(*fen!=' ')
    {   
        switch (*fen)
        {
            case 'K' : castle |= wk;break;
            case 'Q' : castle |= wq;break;
            case 'k' : castle |= bk;break;
            case 'q' : castle |= bq;break;
            case '-' : break;
        }
        fen++;
    }
    fen++;

    //enpassant
    if(*fen!='-')
    {
        int  file = fen[0] - 'a';
        int rank  = 8 - (fen[1]-'0');
        enpassant_sq = rank*8 + file;
    }
    else enpassant_sq = no_sq;
    
    //currently don't need the next  characters in the fen  string

    for(int piece = P; piece<=K; piece++) occupancies[white] |= bitboards[piece];
    for(int piece = p; piece<=k; piece++) occupancies[black] |= bitboards[piece];
    
    occupancies[both] |= occupancies[white];
    occupancies[both] |= occupancies[black];
    return;
}









// ===================================
//             ATTACK TABLES
// ===================================

U64 pawn_attacks[2][64]; // --> 2 means either black or white and 64 means they can have 64 spaces to sit.
U64 knight_attacks[64]; 
U64 king_attacks[64];
U64 bishop_masks[64];
U64 rook_masks[64];
U64 bishop_attacks[64][512]; //// bishop[square][occupancy] --> occupancy is a particular blocking pattern
U64 rook_attacks[64][4096]; // rook[square][occupancy] --> occupancy is a particular blocking pattern


// ===========================================
//             Magic numbers
// ===========================================
U64 rook_magic_numbers[64] = {
    0x8a80104000800020ULL,
    0x140002000100040ULL,
    0x2801880a0017001ULL,
    0x100081001000420ULL,
    0x200020010080420ULL,
    0x3001c0002010008ULL,
    0x8480008002000100ULL,
    0x2080088004402900ULL,
    0x800098204000ULL,
    0x2024401000200040ULL,
    0x100802000801000ULL,
    0x120800800801000ULL,
    0x208808088000400ULL,
    0x2802200800400ULL,
    0x2200800100020080ULL,
    0x801000060821100ULL,
    0x80044006422000ULL,
    0x100808020004000ULL,
    0x12108a0010204200ULL,
    0x140848010000802ULL,
    0x481828014002800ULL,
    0x8094004002004100ULL,
    0x4010040010010802ULL,
    0x20008806104ULL,
    0x100400080208000ULL,
    0x2040002120081000ULL,
    0x21200680100081ULL,
    0x20100080080080ULL,
    0x2000a00200410ULL,
    0x20080800400ULL,
    0x80088400100102ULL,
    0x80004600042881ULL,
    0x4040008040800020ULL,
    0x440003000200801ULL,
    0x4200011004500ULL,
    0x188020010100100ULL,
    0x14800401802800ULL,
    0x2080040080800200ULL,
    0x124080204001001ULL,
    0x200046502000484ULL,
    0x480400080088020ULL,
    0x1000422010034000ULL,
    0x30200100110040ULL,
    0x100021010009ULL,
    0x2002080100110004ULL,
    0x202008004008002ULL,
    0x20020004010100ULL,
    0x2048440040820001ULL,
    0x101002200408200ULL,
    0x40802000401080ULL,
    0x4008142004410100ULL,
    0x2060820c0120200ULL,
    0x1001004080100ULL,
    0x20c020080040080ULL,
    0x2935610830022400ULL,
    0x44440041009200ULL,
    0x280001040802101ULL,
    0x2100190040002085ULL,
    0x80c0084100102001ULL,
    0x4024081001000421ULL,
    0x20030a0244872ULL,
    0x12001008414402ULL,
    0x2006104900a0804ULL,
    0x1004081002402ULL
};

// bishop magic numbers
U64 bishop_magic_numbers[64] = {
    0x40040844404084ULL,
    0x2004208a004208ULL,
    0x10190041080202ULL,
    0x108060845042010ULL,
    0x581104180800210ULL,
    0x2112080446200010ULL,
    0x1080820820060210ULL,
    0x3c0808410220200ULL,
    0x4050404440404ULL,
    0x21001420088ULL,
    0x24d0080801082102ULL,
    0x1020a0a020400ULL,
    0x40308200402ULL,
    0x4011002100800ULL,
    0x401484104104005ULL,
    0x801010402020200ULL,
    0x400210c3880100ULL,
    0x404022024108200ULL,
    0x810018200204102ULL,
    0x4002801a02003ULL,
    0x85040820080400ULL,
    0x810102c808880400ULL,
    0xe900410884800ULL,
    0x8002020480840102ULL,
    0x220200865090201ULL,
    0x2010100a02021202ULL,
    0x152048408022401ULL,
    0x20080002081110ULL,
    0x4001001021004000ULL,
    0x800040400a011002ULL,
    0xe4004081011002ULL,
    0x1c004001012080ULL,
    0x8004200962a00220ULL,
    0x8422100208500202ULL,
    0x2000402200300c08ULL,
    0x8646020080080080ULL,
    0x80020a0200100808ULL,
    0x2010004880111000ULL,
    0x623000a080011400ULL,
    0x42008c0340209202ULL,
    0x209188240001000ULL,
    0x400408a884001800ULL,
    0x110400a6080400ULL,
    0x1840060a44020800ULL,
    0x90080104000041ULL,
    0x201011000808101ULL,
    0x1a2208080504f080ULL,
    0x8012020600211212ULL,
    0x500861011240000ULL,
    0x180806108200800ULL,
    0x4000020e01040044ULL,
    0x300000261044000aULL,
    0x802241102020002ULL,
    0x20906061210001ULL,
    0x5a84841004010310ULL,
    0x4010801011c04ULL,
    0xa010109502200ULL,
    0x4a02012000ULL,
    0x500201010098b028ULL,
    0x8040002811040900ULL,
    0x28000010020204ULL,
    0x6000020202d0240ULL,
    0x8918844842082200ULL,
    0x4010011029020020ULL
};



//setBits count for particulare square for slider piece excluding the edge square
// if it is at a particular square, what are all its available square(attack squares), if no blocker are in the way,
const int bishop_bit_counts[]=
{
    6, 5, 5, 5, 5, 5, 5, 6, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    6, 5, 5, 5, 5, 5, 5, 6
};

const int rook_bit_counts[] = 
{
    12, 11, 11, 11, 11, 11, 11, 12, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    12, 11, 11, 11, 11, 11, 11, 12
};


U64 mask_pawn_attacks(int side, int square)
{
    U64 bitboard = 0ULL;
    U64 attack_bitboard = 0ULL;
    set_bit(bitboard, square);

    if(side==white)
    {
        if((bitboard >> 7) & not_a_file)attack_bitboard |= bitboard >> 7;
        if((bitboard >> 9) & not_h_file) attack_bitboard |= bitboard >> 9;
    }
    else
    {
        if((bitboard << 7) & not_h_file)attack_bitboard |= bitboard << 7;
        if((bitboard << 9) & not_a_file) attack_bitboard |= bitboard << 9;
    } 

    return attack_bitboard;
}


U64 mask_knight_attacks(int square)
{
    U64 bitboard = 0ULL;
    U64 attack_bitboard = 0ULL;
    set_bit(bitboard, square);

    //going up (17,15,10,6)--> steps
    if((bitboard >> 17) & not_h_file) attack_bitboard |= bitboard>>  17;
    if((bitboard >> 15) & not_a_file) attack_bitboard |= bitboard>>  15;
    if((bitboard >> 10) & not_gh_file) attack_bitboard |= bitboard>>  10;
    if((bitboard >> 6) & not_ab_file) attack_bitboard |= bitboard>>  6;

    //moving down 
    if((bitboard << 17) & not_a_file) attack_bitboard |= bitboard << 17;
    if((bitboard << 15) & not_h_file) attack_bitboard |= bitboard << 15;
    if((bitboard << 10) & not_ab_file) attack_bitboard |= bitboard << 10;
    if((bitboard << 6) & not_gh_file) attack_bitboard |= bitboard << 6;

    return attack_bitboard;
}

U64 mask_king_attacks(int square)
{
    U64 bitboard = 0ULL;
    U64 attack_bitboard = 0ULL;
    set_bit(bitboard, square);

    if(bitboard>>1 & not_h_file) attack_bitboard |= bitboard >> 1;
    if(bitboard<<1 & not_a_file) attack_bitboard |= bitboard << 1;
    attack_bitboard |= bitboard >> 8;
    attack_bitboard |= bitboard << 8;

    if(bitboard>>9 & not_h_file) attack_bitboard |= bitboard >>9 ;
    if(bitboard>>7 & not_a_file) attack_bitboard |= bitboard >> 7 ;
    if(bitboard<<9 & not_a_file) attack_bitboard |= bitboard <<9 ;
    if(bitboard<<7 & not_h_file) attack_bitboard |= bitboard << 7 ;

    return attack_bitboard;
}


// Calcluating all the possible attack square for the bishop excluding the edge squares.
// Because, the edge square may have a blocker or not, that doesnt really matter because i can go there any how.
U64 mask_bishop_attacks(int square)
{
    U64 attack_bitboard = 0ULL;
    int rank = square / 8, tr;
    int file = square % 8, tf;

    for(tr=rank+1, tf=file+1; tr<=6 && tf<=6 ; tr++,tf++) set_bit(attack_bitboard, tr*8+tf);
    for(tr=rank+1, tf=file-1; tr<=6 && tf>=1 ; tr++,tf--) set_bit(attack_bitboard, tr*8+tf);
    for(tr=rank-1, tf=file+1; tr>=1 && tf<=6 ; tr--,tf++) set_bit(attack_bitboard, tr*8+tf);
    for(tr=rank-1, tf=file-1; tr>=1 && tf>=1 ; tr--,tf--) set_bit(attack_bitboard, tr*8+tf);

    return attack_bitboard;
}

U64 mask_rook_attacks(int square)
{
    U64 attack_bitboard = 0ULL;
    int r = square / 8, tr;
    int f = square % 8, tf;

    for(tr=r+1; tr<=6; tr++) set_bit(attack_bitboard, tr*8  + f);
    for(tr=r-1; tr>=1; tr--) set_bit(attack_bitboard, tr*8  + f);
    for(tf=f+1; tf<=6; tf++) set_bit(attack_bitboard, r*8  + tf);
    for(tf=f-1; tf>=1; tf--) set_bit(attack_bitboard, r*8  + tf);

    return attack_bitboard;
}

U64 mask_queen_attacks(int square)
{
    U64 bishop_mask = mask_bishop_attacks(square);
    U64 rook_mask =  mask_rook_attacks(square);
    U64 attack_bitboard = 0ULL;
    attack_bitboard |= bishop_mask  | rook_mask;
    return  attack_bitboard;
}
// generating a particular occupancy bitboard for given index (Generates the blocking pattern)
U64 set_occupancy(int index, int set_bits_mask, U64 mask_bishop)
{
    U64 occupancy = 0ULL;
    for(int count = 0; count<set_bits_mask; count++)
    {
        int square = get_ls1b(mask_bishop);
        unset_bit(mask_bishop, square);
        if(index&(1<<count)) set_bit(occupancy, square);
    }
    return occupancy;
}


//Generating the complete ray
U64 bishop_attack_final( U64& occupancy, int square)
{
    U64 bishop_attack_table = 0ULL;
    int rank = square / 8, tr;
    int file = square % 8, tf; 

    for(tr = rank+1, tf=file+1; tr<=7 && tf<=7; tr++, tf++) 
    {
        int target_sq = tr*8 + tf;
        bishop_attack_table |= (1ULL<<target_sq) ;
        if((1ULL<<target_sq ) & occupancy) break;
    }
    for(tr = rank+1, tf=file-1; tr<=7 && tf>=0; tr++, tf--) 
    {
        int target_sq = tr*8 + tf;
        bishop_attack_table |= (1ULL<<target_sq) ;
        if((1ULL<<target_sq ) & occupancy) break;
    }
    for(tr = rank-1, tf=file+1; tr>=0 && tf<=7; tr--, tf++) 
    {
        int target_sq = tr*8 + tf;
        bishop_attack_table |= (1ULL<<target_sq) ;
        if((1ULL<<target_sq ) & occupancy) break;
    }
    for(tr = rank-1, tf=file-1; tr>=0 && tf>=0; tr--, tf--) 
    {
        int target_sq = tr*8 + tf;
        bishop_attack_table |= (1ULL<<target_sq) ;
        if((1ULL<<target_sq ) & occupancy) break;
    }    return bishop_attack_table;
}

U64 rook_attack_final( U64& occupancy, int square)
{
    U64 rook_attack_table = 0ULL;
    int rank = square / 8, tr;
    int file = square % 8, tf; 

    for(tr = rank+1; tr<=7; tr++) 
    {
        int target_sq = tr*8 + file;
        rook_attack_table |= (1ULL<<target_sq) ;
        if((1ULL<<target_sq ) & occupancy) break;
    }
    for(tf=file-1; tf>=0; tf--) 
    {
        int target_sq = rank*8 + tf;
        rook_attack_table |= (1ULL<<target_sq) ;
        if((1ULL<<target_sq ) & occupancy) break;
    }
    for(tr = rank-1; tr>=0; tr--) 
    {
        int target_sq = tr*8 + file;
        rook_attack_table |= (1ULL<<target_sq) ;
        if((1ULL<<target_sq ) & occupancy) break;
    }
    for(tf=file+1; tf<=7; tf++) 
    {
        int target_sq = rank*8 + tf;
        rook_attack_table |= (1ULL<<target_sq) ;
        if((1ULL<<target_sq ) & occupancy) break;
    }

    return rook_attack_table;
}


void init_slider_attacks(int bishop)
{
    for(int square=0; square<64 ; square++)
    {
        bishop_masks[square] = mask_bishop_attacks(square);
        rook_masks[square] = mask_rook_attacks(square);

        //inti current masks
        U64 attack_mask = bishop ? bishop_masks[square] : rook_masks[square];

        //init occpancy indices
        int relevant_set_bits = bishop ? bishop_bit_counts[square] : rook_bit_counts[square];
        int occupancy_indices = 1 << (relevant_set_bits);
        

        for(int i=0;i<occupancy_indices;i++)
        {
            if(bishop)
            {
                U64 occupancy = set_occupancy(i,relevant_set_bits, attack_mask);
                U64 magicIndex = (bishop_magic_numbers[square]*occupancy) >> (64 - relevant_set_bits);
                bishop_attacks[square][magicIndex] = bishop_attack_final(occupancy,square);    
            } 
            else
            {
                U64 occupancy = set_occupancy(i,relevant_set_bits, attack_mask);
                U64 magicIndex = (rook_magic_numbers[square]*occupancy) >> (64 - relevant_set_bits);
                rook_attacks[square][magicIndex] = rook_attack_final(occupancy,square);    
            }  
        }
    }
}




const inline U64 get_bishop_attacks (int square, U64 occupancy)
{
    occupancy &= bishop_masks[square];
    occupancy *= bishop_magic_numbers[square];
    occupancy >>= (64-bishop_bit_counts[square]);
    return bishop_attacks[square][occupancy];
}

const inline U64 get_rook_attacks (int square, U64 occupancy)
{
    occupancy &= rook_masks[square];
    occupancy *= rook_magic_numbers[square];
    occupancy >>= (64-rook_bit_counts[square]);
    return rook_attacks[square][occupancy];
}

const inline U64 get_queen_attacks(int square, U64 occupancy)
{
    U64 result = 0ULL;
    result |= get_bishop_attacks(square, occupancy) | get_rook_attacks(square, occupancy);
    return result;

}



// =========================================
//         Generate Attack Table
// =========================================
void generate_attack_table()
{
    for(int square = 0; square<64; square++)
    {   
        pawn_attacks[white][square] =  mask_pawn_attacks(white, square);
        pawn_attacks[black][square] =  mask_pawn_attacks(black, square);
        knight_attacks[square] = mask_knight_attacks(square);
        king_attacks[square] = mask_king_attacks(square);
    }
}

// ==================================================
//                     Init all 
// ==================================================

void init_all()
{
    init_pieces();
    generate_attack_table();
    init_slider_attacks(1); //1 for bishop 
    init_slider_attacks(0);  // 0 for rook
}

// ============================================================================
//                     Is the  square  under attack
// ============================================================================
static inline int is_square_attacked(int square, int side)
{
    if(side == white)
    {
        if(pawn_attacks[black][square] & (bitboards[P])) return 1;
        if(knight_attacks[square] & bitboards[N]) return 1;
        if(king_attacks[square] & bitboards[K]) return 1;
        if(get_bishop_attacks(square,occupancies[both]) & bitboards[B]) return 1;
        if(get_rook_attacks(square,occupancies[both]) & bitboards[R] ) return 1;
        if(get_queen_attacks(square,occupancies[both]) & bitboards[Q]) return 1; 
    }
    else
    {
        if(pawn_attacks[white][square] & (bitboards[p])) return 1;
        if(knight_attacks[square] & bitboards[n]) return 1;
        if(king_attacks[square] & bitboards[k]) return 1;
        if(get_bishop_attacks(square,occupancies[both]) & bitboards[b]) return 1;
        if(get_rook_attacks(square,occupancies[both]) & bitboards[r] ) return 1;
        if(get_queen_attacks(square,occupancies[both]) & bitboards[q]) return 1;    
    }
    return 0; // Nobody is attacking this particular square.
} 

void print_attacked_square(int side)
{
    std::cout<<"\n";
    for(int rank = 0; rank<=7; rank++)
    {
        for(int file = 0; file<=7 ; file++)
        {
            int square = rank*8 + file;
            if(!file) std:: cout<<8 - rank<<"  ";
            if(is_square_attacked(square, side)) std:: cout<<"1 ";
            else std::cout<<"0 "; 
        }
        std::cout<<"\n";
    }

    std:: cout<<"   a b c d e f g h"<<"\n";   
}



// =======================================================================
//                             Generating moves
// =======================================================================
void generate_moves()
{
    int source_sq, target_sq;
    U64 bitboard, attack;

   
    
    for(int piece = P; piece<=k; piece++)
    {
        
        if(side==white)
        {
            if(piece==P)
            {
                bitboard = bitboards[piece];
                while(bitboard)
                {
                    source_sq = get_ls1b(bitboard);
                    target_sq = source_sq -  8; // moving a step ahead
                    
                    //generating quite moves
                    if(target_sq>=a8 && !(get_bit(occupancies[both], target_sq))) // target sq is within the board and no blockers in its way
                    {
                        // Pawn promotion
                        if(target_sq>=a8 && target_sq<=h8)
                        {
                            std:: cout<< square_to_coordinates[source_sq]<<square_to_coordinates[target_sq]<<" : Pawn Promotion\n";
                        }
                        else //one move ahead, two move ahead
                        {
                            std::cout<<square_to_coordinates[source_sq]<<square_to_coordinates[target_sq]<<" : Pawn push \n";
                            if(source_sq>=a2 && source_sq<=h2) //two move is possible
                            {
                                //can i push for 2 squares?
                                target_sq = source_sq - 16;
                                if(!get_bit(occupancies[both], target_sq)) std::cout<<square_to_coordinates[source_sq]<<square_to_coordinates[target_sq]<<" : Pawn double push \n";
                            }
                        }
                    }

                        //generating capture moves
                        attack = pawn_attacks[white][source_sq] & occupancies[black];
                        
                        while(attack)
                        {
                            int target_attack = get_ls1b(attack);
                            
                            //Promotion capture
                            if(source_sq>=a7 && source_sq<=h7) 
                            {
                                std::cout<< square_to_coordinates[source_sq]<<square_to_coordinates[target_attack]<<" : Pawn promotion caputre\n";
                            }
                            else std::cout<<square_to_coordinates[source_sq]<<square_to_coordinates[target_attack]<<" : Pawn capture\n";
                            unset_bit(attack, target_attack);
                        }
                    
                        //checking for enpassant move
                        if(enpassant_sq!= no_sq)
                        {
                            attack = (1ULL<<enpassant_sq) & pawn_attacks[white][source_sq];
                            if(attack) std::cout<<square_to_coordinates[source_sq]<<square_to_coordinates[enpassant_sq]<<" : Enpassant capture \n";
                        }

                    //poping the lsb
                    unset_bit(bitboard, source_sq);  
                }   
            }

            if(piece==K)
            {
                if(castle & wk)
                {
                    if(get_bit(occupancies[both], f1) || get_bit(occupancies[both], g1)) std::cout<<"Not Possible 0-0 for white\n";
                    else if(is_square_attacked(e1, black) || is_square_attacked(f1, black) || is_square_attacked(g1, black))  std::cout<<"Not Possible 0-0 for white\n";
                    else std::cout<<"0-0 is possible for white\n";
                }
                if(castle & wq)
                {
                    if(get_bit(occupancies[both], b1) || get_bit(occupancies[both], c1) || get_bit(occupancies[both], d1) ) std::cout<<"Not Possible 0-0-0 for white\n";
                    else if(is_square_attacked(e1, black) || is_square_attacked(d1, black) || is_square_attacked(c1, black))  std::cout<<"Not Possible 0-0-0 for white\n";
                    else std::cout<<"0-0-0 is possible for white\n";
                }
                if(!(castle&wk) && !(castle&wq)) std::cout<<"NO castling available\n";
            }
        }

        //side==black
        else
        {
            if(piece==p)
            {
                bitboard = bitboards[p];
                while(bitboard)
                {
                    source_sq = get_ls1b(bitboard);
                    target_sq = source_sq + 8; // moving a step ahead

                    //Pawn quite moves
                    if(target_sq<=h1 && !(get_bit(occupancies[both], target_sq))) // target sq is within the board and no blockers in its way
                    {
                        // Pawn promotion
                        if(target_sq>=a1 && target_sq<=h1)
                        {
                            std:: cout<< square_to_coordinates[source_sq]<<square_to_coordinates[target_sq]<<" : Pawn Promotion\n";
                        }
                        else //one move ahead, two move ahead
                        {
                            std::cout<<square_to_coordinates[source_sq]<<square_to_coordinates[target_sq]<<" : Pawn push \n";
                            if(source_sq>=a7 && source_sq<=h7) //two move is possible
                            {
                                //can i push for 2 squares?
                                target_sq = source_sq + 16;
                                if(!get_bit(occupancies[both], target_sq)) std::cout<<square_to_coordinates[source_sq]<<square_to_coordinates[target_sq]<<" : Pawn double push \n"; 
                            }
                        }

                    }

                    // generating the capture moves
                        attack = pawn_attacks[black][source_sq] & occupancies[white];
                        
                        while(attack)
                        {
                            int target_attack = get_ls1b(attack);

                            //Promotion capture
                            if(source_sq>=a2 && source_sq<=h2) 
                            {
                                std::cout<< square_to_coordinates[source_sq]<<square_to_coordinates[target_attack]<<" : Pawn promotion caputre\n";
                            }
                            else std::cout<<square_to_coordinates[source_sq]<<square_to_coordinates[target_attack]<<" : Pawn capture\n";
                            unset_bit(attack, target_attack);
                        }
                        if(enpassant_sq!= no_sq)
                        {
                            attack = (1ULL<<enpassant_sq) & pawn_attacks[black][source_sq];
                            if(attack) std::cout<<square_to_coordinates[source_sq]<<square_to_coordinates[enpassant_sq]<<" : Enpassant capture\n";
                        }

                    // Popping the lsb
                    unset_bit(bitboard, source_sq);

                }
            }
            if(piece==k )
            {
                    if(castle & bk)
                    {
                        if(get_bit(occupancies[both], f8) || get_bit(occupancies[both], g8)) std::cout<<"Not Possible 0-0 for black\n";
                        else if(is_square_attacked(e8, white) || is_square_attacked(f8, white) || is_square_attacked(g8, white))  std::cout<<"Not Possible 0-0 for black\n";
                        else std::cout<<"0-0 is possible for black\n";
                    }
                    if(castle & bq)
                    {
                        if(get_bit(occupancies[both], b8) || get_bit(occupancies[both], c8) || get_bit(occupancies[both], d8)) std::cout<<"Not Possible 0-0-0 for black\n";
                        else if(is_square_attacked(e8, white) || is_square_attacked(d8, white) || is_square_attacked(c8, white))  std::cout<<"Not Possible 0-0-0 for black\n";
                        else std::cout<<"0-0-0 is possible for black\n";
                    }
                    if(!(castle&bk) && !(castle&bq)) std::cout<<"NO castling available for black\n";
            }
        }

        //whatever be the side, 
        // Knights quiet moves

        if( (side==white) ?   piece == N : piece == n)
        {
            (side == white) ? bitboard = bitboards[N]  : bitboard =  bitboards[n]; 

            while(bitboard)
            {
                source_sq = get_ls1b(bitboard);
                attack = knight_attacks[source_sq] & ((side==white) ? ~occupancies[white] : ~occupancies[black]);
                while(attack)
                {
                    int target_attack = get_ls1b(attack);
                    //quite move
                    if(!get_bit(((side==white) ? occupancies[black] : occupancies[white]), target_attack)) std::cout<<square_to_coordinates[source_sq]<< square_to_coordinates[target_attack]<<" : Knight quite move "<<"\n";
                    //Capture move
                    else std::cout<<square_to_coordinates[source_sq]<< square_to_coordinates[target_attack]<<" : Knight capture move "<<"\n";
                    unset_bit(attack, target_attack);
                }
                unset_bit(bitboard, source_sq);
            }
        }

        //Generating bishop moves
        if(((side==white) ? piece==B : piece==b))
        {
            bitboard = bitboards[piece];

            while(bitboard)
            {
                source_sq = get_ls1b(bitboard);
                attack = get_bishop_attacks(source_sq, occupancies[both]);
                attack = attack & ((side==white) ? ~occupancies[white] : ~occupancies[black]);

                while(attack)
                {
                    int target_attack  = get_ls1b(attack);
                    //quite move
                    if( !(get_bit(((side==white)?occupancies[black] : occupancies[white]),target_attack))) std::cout<<square_to_coordinates[source_sq]<< square_to_coordinates[target_attack]<<" : Bishop quite move "<<"\n";
                    //capture move
                    else std::cout<<square_to_coordinates[source_sq]<< square_to_coordinates[target_attack]<<" : Bishop capture move "<<"\n";
                    unset_bit(attack, target_attack);
                }
                unset_bit(bitboard, source_sq);
            }
        }

        //Generating rook moves
        if((side==white) ? piece==R : piece==r) 
        {
            bitboard = bitboards[piece];
            
            while(bitboard)
            {
                source_sq = get_ls1b(bitboard);
                attack = get_rook_attacks(source_sq, occupancies[both]);
                attack &= ((side == white) ? ~occupancies[white] : occupancies[black]);
                
                while(attack)
                {
                    int target_attack = get_ls1b(attack);
                    //quite move
                    if(!get_bit((side==white)?occupancies[black] : occupancies[white], target_sq)) std::cout<<square_to_coordinates[source_sq]<< square_to_coordinates[target_attack]<<" : Rook quite move "<<"\n";
                    //capture move 
                    else std::cout<<square_to_coordinates[source_sq]<< square_to_coordinates[target_attack]<<" : Rook capture move "<<"\n";
                    unset_bit(attack, target_attack);
                }
                unset_bit(bitboard, source_sq);
            }
        }


        //Generating  moves for queen
        if((side==white) ? piece==Q : piece==q)
        {
            bitboard = bitboards[piece];

            while(bitboard)
            {
                source_sq = get_ls1b(bitboard);
                attack = get_queen_attacks(source_sq, occupancies[both]);
                attack &= ((side==white)? ~occupancies[white] : ~occupancies[black]);

                while(attack)
                {
                    int target_attack = get_ls1b(attack);

                    //quite move
                    if(!get_bit(((side==white) ? occupancies[black] : occupancies[white]), target_attack)) std::cout<<square_to_coordinates[source_sq]<< square_to_coordinates[target_attack]<<" : Queen quite move "<<"\n";
                    //capture move
                    else  std::cout<<square_to_coordinates[source_sq]<< square_to_coordinates[target_attack]<<" : Queen capture move "<<"\n";
                    unset_bit(attack, target_attack);
                }
                unset_bit(bitboard, source_sq);
            }
        }

        //Generating king moves
        if((side==white) ? piece==K : piece==k)
        {
            bitboard = bitboards[piece];

            while(bitboard)
            {
                source_sq = get_ls1b(bitboard);
                attack = king_attacks[source_sq];
                attack &= ((side==white)? ~occupancies[white] : ~occupancies[black]);

                while(attack)
                {
                    int target_attack = get_ls1b(attack);

                    //quite move
                    if(!get_bit(((side==white) ? occupancies[black] : occupancies[white]), target_attack)) std::cout<<square_to_coordinates[source_sq]<< square_to_coordinates[target_attack]<<" : King quite move "<<"\n";
                    //capture move
                    else  std::cout<<square_to_coordinates[source_sq]<< square_to_coordinates[target_attack]<<" : King capture move "<<"\n";
                    unset_bit(attack, target_attack);
                }
                unset_bit(bitboard, source_sq);
            }
        }
    }
}

// ===================================
//             MAIN FUNC
// ===================================

int main()
{
    // init all
    init_all();
    
    // parse custom FEN string
    parser_fen("r2nk2r/p1ppqpb1/b3pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQk - 0 1 ");
    print_board();
    
    // generate moves
    generate_moves();

    return 0;
}