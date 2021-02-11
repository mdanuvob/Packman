/*Author: Md. Anuvob, Mahmudul Hasan
    Date:3-4-2017
*/
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;
char tmp_box[23][70];

char box[23][70]={
    "###############################################################",
    "#                                                             #",
    "# ############### ######################## ################## #",
    "# #             # #                      # #                # #",
    "# # ########### # #  ####           #### # #  ####    ####  # #",
    "# # #         # # #  #  #           #  # # #  #  #    #  #  # #",
    "# # #   ####### # #  #  #           #  # # #  #  #    #  #  # #",
    "# # #   #       # #  #  #           #  # # #  #  #    #  #  # #",
    "# # #   #####   # #  #  #           #  # # #  #  #    #  #  # #",
    "# # #       #   # #  #  #           #  # # #  #  #    #  #  # #",
    "# # #   #####   # #   #  #    #    #  #  # #  #  #    #  #  # #",
    "# # #   #       # #    #  #  # #  #  #   # #  #  #    #  #  # #",
    "# # #   ####### # #     #   #   #   #    # #  #  ######  #  # #",
    "# # #         # # #      #  #   #  #     # #   #        #   # #",
    "# # ########### # #       ###   ###      # #    ########    # #",
    "# #             # #                      # #                # #",
    "# ############### ######################## ################## #",
    "#                                                             #",
    "# ############ ##################### ######################## #",
    "# #          # #                   # #                      # #",
    "# ############ ##################### ######################## #",
    "#                                                             #",
    "###############################################################",
    };
void Showbox()
{
	for(int i = 0; i < 23; i++) {
		printf("%s\n",box[i] );
	}
}

void gotoxy( short x, short y )
{
    HANDLE dout = GetStdHandle(STD_OUTPUT_HANDLE) ;
     COORD position = { x , y } ;

    SetConsoleCursorPosition( dout, position ) ;
}

class process {
    int x,y;

public:
	process( int x, int y ){
		this ->x = x;
		this ->y = y;
	}

	void move_x( int p ){
		if( box[y][x+p] == ' ' ) x += p;
	}

	void move_y( int p ){
		if( box[y+p][x] == ' ' ) y += p;
	}

	void move( int p, int q ){
		x += p;
		y += q;
	}

	int get_x(){ return x; }
	int get_y(){ return y; }

	void draw( char p ){
		box[x][y] = p;
		gotoxy( x, y ); printf( "%c", p );
	}

};

struct walk {
	short walk_count;
	short x;
	short y;
	short back;
};

struct target {
	short x;
	short y;
};

vector<target> walk_queue;

vector<walk> fast;


void AddArray( int x, int y, int wc , int back ){
	if( tmp_box[y][x] == ' ' || tmp_box[y][x] == '.' ){
		tmp_box[y][x] = '#';
		walk tmp;
		tmp.x = x;
		tmp.y = y;
		tmp.walk_count = wc;
		tmp.back = back;
		fast.push_back( tmp );
	}
}

void FindPath( int sx, int sy, int x, int y ){
	memcpy( tmp_box,box, sizeof(box) );
	fast.clear();
	walk tmp;
	tmp.x = sx;
	tmp.y = sy;
	tmp.walk_count = 0;
	tmp.back = -1;
	fast.push_back( tmp );

	int i = 0;
	while( i < fast.size() ){
		if( fast[i].x == x && fast[i].y == y ){
			walk_queue.clear();
			target tmp2;
			while( fast[i].walk_count != 0 ){
				tmp2.x = fast[i].x;
				tmp2.y = fast[i].y;
				walk_queue.push_back( tmp2 );

				i = fast[i].back;
			}

			break;
		}

		AddArray( fast[i].x+1, fast[i].y, fast[i].walk_count+1, i );
		AddArray( fast[i].x-1, fast[i].y, fast[i].walk_count+1, i );
		AddArray( fast[i].x, fast[i].y+1, fast[i].walk_count+1, i );
		AddArray( fast[i].x, fast[i].y-1, fast[i].walk_count+1, i );
		i++;
	}

	fast.clear();
}


int main()
{
    bool running = true;
	int x = 15;
	int y = 17;
	int old_x;
	int old_y;

	int ex = 1;
	int ey = 1;


	int POINTS = 0;

	printf("Please Follow The Instructions Below:\n\n1. press any arrow Keys to move your hero\n2. Eat the dots produced by the Eater to increase your points\n3. Don't get caught by the Eater\n4. Go Ahead Best Of Luck\n\n");
	printf("H -> Hard\nN -> Normal\nE -> Easy\n\nChoose Level : ");

	char diffi;
	int speedmod = 4;

	cin >> diffi;

	if( diffi == 'N' ){
		speedmod = 2;
	}else if( diffi == 'H' ){
		speedmod = 1;
	}

	system("cls");
    Showbox();

	gotoxy( x, y ); cout << "H";

	int frame = 0;

	FindPath( ex,ey,x,y );

	while( running ){
		gotoxy( x, y ); cout << " ";

		old_x = x;
		old_y = y;

		if ( GetAsyncKeyState( VK_UP ) ){
			if( box[y-1][x] == '.' ){ y--; POINTS++; } else
			if( box[y-1][x] == ' ' ) y--;
		}
		if ( GetAsyncKeyState( VK_DOWN ) ){
			if( box[y+1][x] == '.' ){ y++; POINTS++; } else
			if( box[y+1][x] == ' ' ) y++;
		}
		if ( GetAsyncKeyState( VK_LEFT ) ){
			if( box[y][x-1] == '.' ){ x--; POINTS++; } else
			if( box[y][x-1] == ' ' ) x--;
		}
		if ( GetAsyncKeyState( VK_RIGHT ) ){
			if( box[y][x+1] == '.' ){ x++; POINTS++; } else
			if( box[y][x+1] == ' ' ) x++;
		}

		if( old_x != x || old_y != y ){
			FindPath( ex,ey,x,y );
		}

		gotoxy( x,y ); cout << "H";

		box[ey][ex] = '.';
		gotoxy( ex, ey ); cout << ".";

		if( frame%speedmod == 0 && walk_queue.size() != 0 ){
			ex = walk_queue.back().x;
			ey = walk_queue.back().y;
			walk_queue.pop_back();
		}

		gotoxy( ex, ey ); cout << "S";

		if( ex == x && ey == y ){
			break;
		}


		gotoxy( 70, 23 );
		gotoxy( 70, 1);
        cout << POINTS;
		Sleep( 100 );
		frame++;
	}

	system("cls");
	printf("You get caught and your score is : %i", POINTS );
	cin.get();
	cin.get();
	cin.get();
	cin.get();
	cin.get();
	cin.get();
	cin.get();
	cin.get();

	return 0;
}

