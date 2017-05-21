/* This was done in Fall 2016. */
/* This was a simple database project. I chose to use data pertaining to the video game Street Fighter 5 because it was the first thing that came to mind.*/

CREATE DATABASE Fighters;

CREATE TABLE Players
(
FirstName varchar(255) NOT NULL,
LastName varchar(255) NOT NULL,
Alias varchar(255) NOT NULL,
Nationality varchar(255) NOT NULL,
PRIMARY KEY (Alias)
);

CREATE TABLE Tournaments
(
TourneyName varchar(255) NOT NULL,
StartDate varchar(255) NOT NULL,
EndDate varchar(255) NOT NULL,
Location varchar(255) NOT NULL,
PRIMARY KEY (TourneyName,StartDate)
);

CREATE TABLE WonTournament
(
TourneyName varchar(255) NOT NULL,
TourneyWinner varchar(255),
FOREIGN KEY (TourneyName) REFERENCES Tournaments(TourneyName) ON DELETE CASCADE,
FOREIGN KEY (TourneyWinner) REFERENCES Players(Alias) ON DELETE SET NULL,
PRIMARY KEY (TourneyName)
);

CREATE TABLE Characters
(
CharName varchar(255) NOT NULL,
Health int NOT NULL,
Stun int NOT NULL,
PRIMARY KEY (CharName)
);

delimiter //
CREATE TRIGGER health_check BEFORE INSERT ON Characters
FOR EACH ROW
BEGIN
	IF NEW.Health < 850 THEN
		SET NEW.Health = 850;
	END IF;
	IF NEW.Stun < 850 THEN
		SET NEW.Stun = 850;
	END IF;
END;//
delimiter ;

CREATE TABLE PlaysCharacter
(
PlayerAlias varchar(255) NOT NULL,
CharName varchar(255) NOT NULL,
FOREIGN KEY (PlayerAlias) REFERENCES Players(Alias) ON DELETE CASCADE,
FOREIGN KEY (CharName) REFERENCES Characters(CharName) ON DELETE CASCADE,
PRIMARY KEY (PlayerAlias, CharName)
);

CREATE TABLE Moves
(
MoveName varchar(255) NOT NULL,
Archetype varchar(255) NOT NULL,
MoveUser varchar(255) NOT NULL,
FOREIGN KEY (MoveUser) REFERENCES Characters(CharName) ON DELETE CASCADE,
PRIMARY KEY (MoveName, MoveUser)
);

INSERT INTO Players (FirstName, LastName, Alias, Nationality)
VALUES ('Seonwoo', 'Lee', 'Infiltration', 'Korea');

INSERT INTO Players (FirstName, LastName, Alias, Nationality)
VALUES ('Hajime', 'Taniguchi', 'Tokido', 'Japan');

INSERT INTO Players (FirstName, LastName, Alias, Nationality)
VALUES ('Justin', 'Wong', 'Justin Wong', 'USA');

INSERT INTO Players (FirstName, LastName, Alias, Nationality)
VALUES ('Daigo', 'Umehara', 'Daigo Umehara', 'Japan');

INSERT INTO Players (FirstName, LastName, Alias, Nationality)
VALUES ('Du', 'Dang', 'NuckleDu', 'USA');

INSERT INTO Players (FirstName, LastName, Alias, Nationality)
VALUES ('Keita', 'Ai', 'Fuudo', 'Japan');

INSERT INTO Players (FirstName, LastName, Alias, Nationality)
VALUES ('Zhuojun', 'Zeng', 'Xiao Hai', 'China');

INSERT INTO Players (FirstName, LastName, Alias, Nationality)
VALUES ('Bruce', 'Hsiang', 'GamerBee', 'Taiwan');

INSERT INTO Players (FirstName, LastName, Alias, Nationality)
VALUES ('Joe', 'Egami', 'MOV', 'Japan');

INSERT INTO Players (FirstName, LastName, Alias, Nationality)
VALUES ('Julio', 'Fuentes', 'Julio Fuentes', 'USA');

INSERT INTO Players (FirstName, LastName, Alias, Nationality)
VALUES ('Ryan', 'Ramirez', 'Filipino Champ', 'USA');

INSERT INTO Players (FirstName, LastName, Alias, Nationality)
VALUES ('Ray', 'Rosario', 'DR Ray', 'Dominican Republic');

INSERT INTO Players (FirstName, LastName, Alias, Nationality)
VALUES ('Kenryo', 'Hayashi', 'Mago', 'Japan');

INSERT INTO Tournaments (TourneyName, StartDate, EndDate, Location)
VALUES ('Capcom Cup 2016', '12-02-2016', '12-03-2016', 'Anaheim, CA, USA');

INSERT INTO Tournaments (TourneyName, StartDate, EndDate, Location)
VALUES ('Capcom Pro Tour - Asia/Oceania Regional Finals', '11-17-2016', '11-19-2016', 'South Korea');

INSERT INTO Tournaments (TourneyName, StartDate, EndDate, Location)
VALUES ('NA Regional Finals: Red Bull Battle Grounds', '11-04-2016', '11-06-2016', 'Seattle, WA, USA');

INSERT INTO Tournaments (TourneyName, StartDate, EndDate, Location)
VALUES ('Capcom Pro Tour - Latin America Regional Finals', '10-29-2016', '11-02-2016', 'Sao Paulo, Brazil');

INSERT INTO Tournaments (TourneyName, StartDate, EndDate, Location)
VALUES ('Canada Cup', '10-28-2016', '10-30-2016', 'Toronto, Canada');

INSERT INTO Tournaments (TourneyName, StartDate, EndDate, Location)
VALUES ('EU Regional Finals at Milan Games Week', '10-15-2016', '10-16-2016', 'Milan, Italy');

INSERT INTO Tournaments (TourneyName, StartDate, EndDate, Location)
VALUES ('SoCal Regionals', '10-14-2016', '10-16-2016', 'Los Angeles, CA, USA');

INSERT INTO Tournaments (TourneyName, StartDate, EndDate, Location)
VALUES ('South East Asia Major 2016', '10-07-2016', '10-09-2016', 'Singapore');

INSERT INTO Tournaments (TourneyName, StartDate, EndDate, Location)
VALUES ('EGX', '09-22-2016', '09-25-2016', 'Birmingham, England');

INSERT INTO Tournaments (TourneyName, StartDate, EndDate, Location)
VALUES ('Japan Cup 2016', '09-17-2016', '09-18-2016', 'Tokyo, Japan');

INSERT INTO Tournaments (TourneyName, StartDate, EndDate, Location)
VALUES ('Evolution Championship Series', '07-15-2016', '07-17-2016', 'Las Vegas, NV, USA');

INSERT INTO WonTournament (TourneyName, TourneyWinner)
VALUES ('Capcom Cup 2016', 'NuckleDu');

INSERT INTO WonTournament (TourneyName, TourneyWinner)
VALUES ('Capcom Pro Tour - Asia/Oceania Regional Finals', 'Mago');

INSERT INTO WonTournament (TourneyName, TourneyWinner)
VALUES ('NA Regional Finals: Red Bull Battle Grounds', 'NuckleDu');

INSERT INTO WonTournament (TourneyName, TourneyWinner)
VALUES ('Capcom Pro Tour - Latin America Regional Finals', 'DR Ray');

INSERT INTO WonTournament (TourneyName, TourneyWinner)
VALUES ('Canada Cup', 'NuckleDu');

INSERT INTO WonTournament (TourneyName, TourneyWinner)
VALUES ('EU Regional Finals at Milan Games Week', 'Daigo Umehara');

INSERT INTO WonTournament (TourneyName, TourneyWinner)
VALUES ('SoCal Regionals', 'Xiao Hai');

INSERT INTO WonTournament (TourneyName, TourneyWinner)
VALUES ('South East Asia Major 2016', 'Tokido');

INSERT INTO WonTournament (TourneyName, TourneyWinner)
VALUES ('EGX', 'GamerBee');

INSERT INTO WonTournament (TourneyName, TourneyWinner)
VALUES ('Japan Cup 2016', 'GamerBee');

INSERT INTO WonTournament (TourneyName, TourneyWinner)
VALUES ('Evolution Championship Series', 'Infiltration');

INSERT INTO Characters (CharName, Health, Stun)
VALUES ('Ryu', 1000, 1000);

INSERT INTO Characters (CharName, Health, Stun)
VALUES ('Ken', 1000, 1000);

INSERT INTO Characters (CharName, Health, Stun)
VALUES ('Chun-Li', 950, 1000);

INSERT INTO Characters (CharName, Health, Stun)
VALUES ('Cammy', 900, 900);

INSERT INTO Characters (CharName, Health, Stun)
VALUES ('Necalli', 1000, 1000);

INSERT INTO Characters (CharName, Health, Stun)
VALUES ('R. Mika', 950, 1000);

INSERT INTO Characters (CharName, Health, Stun)
VALUES ('Karin', 900, 950);

INSERT INTO Characters (CharName, Health, Stun)
VALUES ('Guile', 950, 950);

INSERT INTO Characters (CharName, Health, Stun)
VALUES ('Nash', 950, 950);

INSERT INTO Characters (CharName, Health, Stun)
VALUES ('Vega', 1000, 950);

INSERT INTO Characters (CharName, Health, Stun)
VALUES ('Dhalsim', 900, 950);

/* This is just to showcase the trigger.
This character has no moves in the database.
Also, Akuma seems to have 875 health in Street Fighter 5!  */
INSERT INTO Characters (CharName, Health, Stun)
VALUES ('Akuma', 825, 825);

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('Infiltration', 'Nash');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('Infiltration', 'Vega');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('Tokido', 'Ryu');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('Justin Wong', 'Karin');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('Daigo Umehara', 'Ryu');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('NuckleDu', 'Guile');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('NuckleDu', 'R. Mika');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('NuckleDu', 'Nash');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('Fuudo', 'R. Mika');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('Xiao Hai', 'Cammy');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('GamerBee', 'Necalli');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('MOV', 'Chun-Li');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('Julio Fuentes', 'Ken');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('Filipino Champ', 'Dhalsim');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('DR Ray', 'Vega');

INSERT INTO PlaysCharacter (PlayerAlias, CharName)
VALUES ('Mago', 'Karin');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Hadoken', 'Fireball', 'Ryu');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Shoryuken', 'Dragon Punch', 'Ryu');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Tatsumaki Senpukyaku', 'Tatsu', 'Ryu');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Hadoken', 'Fireball', 'Ken');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Shoryuken', 'Dragon Punch', 'Ken');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Tatsumaki Senpukyaku', 'Tatsu', 'Ken');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Kikoken', 'Fireball', 'Chun-Li');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Hyakuretsukyaku', 'Other', 'Chun-Li');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Spinning Bird Kick', 'Other', 'Chun-Li');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Cannon Spike', 'Dragon Punch', 'Cammy');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Cannon Strike', 'Divekick', 'Cammy');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Spiral Arrow', 'Other', 'Cammy');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Hooligan Combination', 'Other', 'Cammy');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Raging Light', 'Dragon Punch', 'Necalli');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Valiant Rebellion', 'Other', 'Necalli');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('The Discs Guidance', 'Rush Punch', 'Necalli');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Mask of Tlalli', 'Command Grab', 'Necalli');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Kanzuki-Ryu Hokojutsu Sappo', 'Command Dash', 'Karin');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Ressenha', 'Other', 'Karin');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Mujinkyaku', 'Other', 'Karin');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Shooting Peach', 'Other', 'R. Mika');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Wingless Airplane', 'Air Grab', 'R. Mika');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Rainbow Typhoon', 'Command Grab', 'R. Mika');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Brimstone', 'Command Grab', 'R. Mika');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Sonic Boom', 'Fireball', 'Guile');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Somersault Kick', 'Dragon Punch', 'Guile');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Sonic Boom', 'Fireball', 'Nash');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Sonic Scythe', 'Other', 'Nash');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Moonsault Slash', 'Other', 'Nash');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Tragedy Assault', 'Hit Grab', 'Nash');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Aurora Spin Edge', 'Other', 'Vega');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Crimson Terror', 'Other', 'Vega');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Flying Barcelona Attack', 'Other', 'Vega');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Grand Izuna Drop', 'Command Grab', 'Vega');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Switch Claw', 'Stance Change', 'Vega');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Yoga Fire', 'Fireball', 'Dhalsim');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Yoga Flame', 'Other', 'Dhalsim');

INSERT INTO Moves (MoveName, Archetype, MoveUser)
VALUES ('Yoga Teleport', 'Teleport', 'Dhalsim');