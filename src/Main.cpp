#include "Game.h"
#include "AccountsManager.h"
#include "User.h"
#include "MultipleAnswerQuestion.h"
#include "NumericalAnswerQuestion.h"
#include "NumericalAnswerQuestion.cpp"
#include "Quiz.h"

int main()
{
    // testing for game
    Player player1("Sebi", Player::Color::Blue);
    Player player2("George", Player::Color::Red);
    Player player3("Marius", Player::Color::Green);
    Game game(player1, player2, player3);
    game.Start();

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
    Quiz quiz;
    quiz.Start();
    

    return 0;
}
