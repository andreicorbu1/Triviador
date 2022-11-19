#include "Game.h"
#include "AccountsManager.h"
#include "User.h"
#include "BasicQuestion.h"
#include "MultipleAnswerQuestion.h"

int main()
{
    // testing for game
    Game game(Player(), Player());
    
    //testing for board&teritory
    Board board(5, 3);

    Player player1("Sebi", Player::Color::Blue);
    Player player2("George", Player::Color::Red);
    Territory t1(player1);
    Territory t2(player2);

    board[{0, 0}] = t1;
    board[{1, 2}] = t2;

    std::cout << board;

    //testing for User and AccountsManager
    User user("2cristianciortea", "123456sadS@");
    User user2("3cristianciortea", "123456Dsa");
    User user3("4cristianciortea", "12345621as");
    User user4("5cristianciortea", "123456#");
    User user5("6cristianciortea", "12345aSs@6");
    user.SetGamesPlayed(2);
    AccountManager userList;
    userList.AddUser(user);
    userList.AddUser(user2);
    userList.AddUser(user3);
    userList.AddUser(user4);
    userList.AddUser(user5);
    std::cout << userList.GetUser("2cristianciortea").GetUsername() << "\n";
    std::cout << userList;
    userList.DeleteUser(user5.GetUsername());
    std::cout << userList;

    //testing for QuestionManager

    BasicQuestion basic_question;
    std::cin >> basic_question;
    std::cout << basic_question;
    MultipleAnswerQuestion maq;
    std::cin >> maq;
    std::cout << maq;

    return 0;
}
