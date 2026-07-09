#include <iostream>
#include <bitset>

#define U64 unsigned long long


//board squares through chess notation and pieces
enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
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

enum{white, black};

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
inline bool get_bit(U64 &bitboard, int sq_number) {return (bitboard & (1ULL<<sq_number)) ? 1 : 0; } 
inline void unset_bit(U64 &bitboard, int sq_number) {bitboard = bitboard &  ~(1ULL<<sq_number);} 
inline int get_ls1b(U64 &bitboard) {if (bitboard) return __builtin_ctzll(bitboard);return -1;}
inline int get_all1b(U64 &bitboard) {return __builtin_popcountll(bitboard);}
    
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

    if(!side)
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
    if((bitboard << 17) & not_gh_file) attack_bitboard |= bitboard << 6;

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

const inline U64 get_queen_attakcs(int square, U64 occupancy)
{
    occupancy &= mask_rook_attacks(square);
    occupancy *= rook_magic_numbers[square];
    occupancy >>= (64-rook_bit_counts[square]);
    return bishop_attacks[square][occupancy] | rook_attacks[square][occupancy];
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
    generate_attack_table();
    init_slider_attacks(1); //1 for bishop 
    init_slider_attacks(0);  // 0 for rook
}


// ===================================
//             MAIN FUNC
// ===================================
unsigned int state = 1804289383;
int main()
{
    std::cout<<"\n--- Booting Chess Engine ---\n";
    init_all();
    std::cout<<"Magic Bitboards fully initialized!\n\n";
    
    // ==========================================
    // TEST 1: Rook on d4 (Empty Board)
    // Expected: Should draw a perfect cross reaching all edges
    // ==========================================
    std::cout << "TEST 1: Rook on d4 (Empty Board)\n";
    U64 empty_board = 0ULL;
    U64 rook_empty = get_rook_attacks(d4, empty_board);
    print_bitboard(rook_empty);

    // ==========================================
    // TEST 2: Bishop on d4 (Trapped by pieces)
    // Expected: Rays should stop exactly ON the blocking pieces
    // ==========================================
    std::cout << "TEST 2: Bishop on d4 (Trapped by pieces on c5, e5, c3, e3)\n";
    U64 trapped_blockers = 0ULL;
    set_bit(trapped_blockers, c5);
    set_bit(trapped_blockers, e5);
    set_bit(trapped_blockers, c3);
    set_bit(trapped_blockers, e3);
    
    U64 bishop_trapped = get_bishop_attacks(d4, trapped_blockers);
    print_bitboard(bishop_trapped);

    // ==========================================
    // TEST 3: Rook on a1 (Corner of the board)
    // Expected: Should only attack North and East. 
    // Bug Check: Ensure it doesn't wrap around to the h-file!
    // ==========================================
    std::cout << "TEST 3: Rook on a1 (Corner, Blocked at a3 and c1)\n";
    U64 corner_blockers = 0ULL;
    set_bit(corner_blockers, a3);
    set_bit(corner_blockers, c1);
    
    U64 rook_corner = get_rook_attacks(a1, corner_blockers);
    print_bitboard(rook_corner);

  
    return 0;
} 