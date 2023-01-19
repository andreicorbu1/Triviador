# Triviador

# How the application works
<ol>
<li>At startup, a user is given the option to log in to their account or they can create an account. Login / registration involves entering the username and a password.

<strong>Warning: username must be unique and the password must be at least 8 characters and have at least one digit, one special character and one capital letter!</strong>
</li>
<li>
The client is prompted by the main menu where he can create or join a game and see his games history.
</li>
<li>
After a client joins the lobby, the lobby can be started if the number of players in that lobby is bigger than 2. The lobby automatically starts if lobby timer expires.
</li>
<li>
<ul><li>
When the game starts all the players are prompted with a numerical answer questions and the server expects their answers.
</li>
<li>
After the server receives the answers the players are being poped out of a priority queue based on the closeness of their answer and the fastest time.
</li>
<li>
The players are prompted to choose a territory where their base will be set.
</li>
<li>
The game continues like this until all the territories are occupied.
</li>
<li>
Then the duel phase starts. Here players attack each other by a random order. If the attacker gets the correct answer faster than the defender, then the attacker gets the territory(only if the score is equal to 100, otherwise the score of the territory is decreased by 100).
</li>
<li>
The game continues like this until there are no rounds remaining or a player conquers all the territories.
</li>
<li>
At the end of the game the players are prompted with the leaderboards of that game and their progress is being saved in the database.
</li>
</ul>
</li>
</ol>

# Advanced project components
<ol>
  <li><strong>GUI</strong> - graphical interface for all the functionalities of the game ( Done using Qt Framework )</li>
  <li><strong>Networking</strong> - the communication between client and server applications ( Done using Crow & CPR ) </li>
  <li><strong>Database</strong> - the data used by the server will be manipulated using a database ( Done using SQLite ORM ) </li>
</ol>

# Teammates
[Bostan Adrian](https://github.com/AdrianBostan2002) \
[Boscan Tiberiu](https://github.com/tbtiberiu) \
[Ciortea Cristian](https://github.com/CristianGabrielCiortea)

# Presentation(click on the image)
[![Watch the video](https://i.imgur.com/Rc0FWrG.png)](https://youtu.be/uKHwdF60wvY)