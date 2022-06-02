CC = gcc 
FLAGS = -c -Wall -ansi -pedantic
LIBRARY = -lm
T = test/
D = doc/
I = include/
L = lib/
O = obj/
S = src/

all: juego

$(O)command.o: $(S)command.c $(I)command.h
	$(CC) -o $@ $(FLAGS) $<
	
$(O)enemy.o: $(S)enemy.c $(I)enemy.h
	$(CC) -o $@ $(FLAGS) $< $(LIBRARY)
	
$(O)game_managment.o: $(S)game_managment.c $(I)game_managment.h $(I)command.h $(I)space.h $(I)types.h $(I)game.h
	$(CC) -o $@ $(FLAGS) $<

$(O)game.o: $(S)game.c $(I)game.h $(I)command.h $(I)space.h $(I)types.h $(I)link.h $(I)player.h $(I)object.h $(I)enemy.h $(I)inventory.h
	$(CC) -o $@ $(FLAGS) $<
	
$(O)graphic_engine.o: $(S)graphic_engine.c $(I)graphic_engine.h $(I)libscreen.h $(I)command.h $(I)space.h $(I)types.h $(I)inventory.h $(I)set.h
	$(CC) -o $@ $(FLAGS) $< $(LIBRARY)

$(O)link.o: $(S)link.c $(I)link.h
	$(CC) -o $@ $(FLAGS) $<
	
$(O)object.o: $(S)object.c $(I)object.h $(I)types.h
	$(CC) -o $@ $(FLAGS) $< $(LIBRARY)
	
$(O)player.o: $(S)player.c $(I)player.h $(I)object.h $(I)inventory.h
	$(CC) -o $@ $(FLAGS) $< $(LIBRARY)
	
$(O)set.o: $(S)set.c $(I)set.h
	$(CC) -o $@ $(FLAGS) $<

$(O)inventory.o: $(S)inventory.c $(I)inventory.h $(I)set.h
	$(CC) -o $@ $(FLAGS) $<

$(O)space.o: $(S)space.c $(I)space.h $(I)types.h $(I)set.h $(I)object.h
	$(CC) -o $@ $(FLAGS) $< $(LIBRARY)

$(O)game_loop.o: $(S)game_loop.c $(I)game.h $(I)command.h $(I)graphic_engine.h
	$(CC) -o $@ $(FLAGS) $< 

$(O)game_rules.o: $(S)game_rules.c $(I)game_rules.h
	$(CC) -o $@ $(FLAGS) $<

$(O)dialogue.o: $(S)dialogue.c $(I)dialogue.h
	$(CC) -o $@ $(FLAGS) $<

juego: $(O)command.o $(O)game.o $(O)game_managment.o $(O)graphic_engine.o $(O)object.o $(O)link.o $(O)player.o $(O)space.o $(O)game_loop.o $(L)libscreen.a $(O)enemy.o $(O)set.o $(O)inventory.o $(O)game_rules.o $(O)dialogue.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)

#GAME
run:
	@echo ">>>>>>Running main"
	./juego map.dat
	
run_test:
	@echo ">>>>>>Running main"
	./juego hola.dat
	
vrun:
	@echo ">>>>>>Running main"
	valgrind --leak-check=full --track-origins=yes ./juego map.dat

runcmd1:
	@echo ">>>>>>Running main from partida1.cmd"
	./juego hormiguero.dat < partida1.cmd 

runcmd2:
	@echo ">>>>>>Running main from partida2.cmd"
	./juego hormiguero.dat < partida2.cmd
	
runlog:
	@echo ">>>>>>Running main and saving commands in file.log"
	./juego map.dat -l file.log

runcmd1log:
	@echo ">>>>>>Running main from partida1.cmd and saving in file.log"
	./juego map.dat -l file.log < partida1.cmd 

runvcmd1log:
	@echo ">>>>>>Running main with valgrind"
	valgrind --leak-check=full ./juego map.dat -l file.log < partida1.cmd 

juego_permisos: juego
	chmod u+x ./juego

#DOXYGEN
doxygen:
	@echo ">>>>>Creating project documentation with doxygen"
	doxygen ./doc/Doxyfile

#ENEMY_TEST
$(O)enemy_test.o: $(T)enemy_test.c $(T)enemy_test.h $(T)test.h $(I)enemy.h
	$(CC) -o $@ $(FLAGS) $<

enemy_test: $(O)enemy_test.o $(O)enemy.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)

venemy_test: enemy_test
	valgrind --leak-check=full ./enemy_test


#SET_TEST
$(O)set_test.o: $(T)set_test.c $(T)set_test.h $(T)test.h $(I)set.h
	$(CC) -o $@ $(FLAGS) $<

set_test: $(O)set_test.o $(O)set.o 
	$(CC) -o $@ -Wall $^ $(LIBRARY)

vset_test: set_test
	valgrind --leak-check=full ./set_test


#SPACE_TEST
$(O)space_test.o: $(T)space_test.c $(T)space_test.h $(T)test.h $(I)space.h
	$(CC) -o $@ $(FLAGS) $<

space_test: $(O)space_test.o $(O)space.o $(O)object.o $(O)set.o $(O)link.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)

vspace_test: space_test
	valgrind --leak-check=full ./space_test


#INVENTORY_TEST
$(O)inventory_test.o: $(T)inventory_test.c $(T)inventory_test.h $(T)test.h $(I)inventory.h
	$(CC) -o $@ $(FLAGS) $<

inventory_test: $(O)inventory_test.o $(O)inventory.o $(O)object.o $(O)set.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)

vinventory_test: inventory_test
	valgrind --leak-check=full ./inventory_test
	

#OBJECT_TEST
$(O)object_test.o: $(T)object_test.c $(T)object_test.h $(T)test.h $(I)object.h
	$(CC) -o $@ $(FLAGS) $<

object_test: $(O)object_test.o $(O)space.o $(O)object.o $(O)set.o $(O)link.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)

vobject_test: object_test
	valgrind --leak-check=full ./object_test
	
	
#PLAYER_TEST
$(O)player_test.o: $(T)player_test.c $(T)player_test.h $(T)test.h $(I)player.h
	$(CC) -o $@ $(FLAGS) $<

player_test: $(O)player_test.o $(O)player.o $(O)object.o $(O)set.o $(O)inventory.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)

vplayer_test: player_test
	valgrind --leak-check=full ./player_test


#LINK_TEST
$(O)link_test.o: $(T)link_test.c $(T)link_test.h $(T)test.h $(I)link.h
	$(CC) -o $@ $(FLAGS) $<

link_test: $(O)link_test.o $(O)link.o $(O)space.o $(O)set.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)

vlink_test: link_test
	valgrind --leak-check=full ./link_test


#GAME_TEST
$(O)game_test.o: $(T)game_test.c $(T)game_test.h $(T)test.h $(I)game.h
	$(CC) -o $@ $(FLAGS) $<

game_test: $(O)game_test.o $(O)game.o $(O)object.o $(O)space.o $(O)player.o $(O)enemy.o $(O)inventory.o $(O)set.o $(O)link.o $(O)dialogue.o $(O)game_rules.o $(O)game_managment.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)

vgame_test: game_test
	valgrind --leak-check=full ./game_test


#DIALOGUE_TEST
$(O)dialogue_test.o: $(T)dialogue_test.c $(T)dialogue_test.h $(T)test.h $(I)dialogue.h
	$(CC) -o $@ $(FLAGS) $<

dialogue_test: $(O)dialogue_test.o $(O)dialogue.o $(O)space.o $(O)enemy.o $(O)object.o $(O)set.o $(O)link.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)

vdialogue_test: dialogue_test
	valgrind --leak-check=full ./dialogue_test


#GAME_RULES_TEST
$(O)game_rules_test.o: $(T)game_rules_test.c $(T)game_rules_test.h $(T)test.h $(I)game_rules.h
	$(CC) -o $@ $(FLAGS) $<

game_rules_test: $(O)game_rules_test.o $(O)game_rules.o
	$(CC) -o $@ -Wall $^ $(LIBRARY)

vgame_rules_test: game_rules_test
	valgrind --leak-check=full ./game_rules_test


all_test: player_test object_test inventory_test set_test enemy_test link_test game_test space_test game_rules_test

#CLEAN
oclean:
	rm -f obj/*.o

xclean:
	rm -f juego
	rm -f *_test

sclean: oclean xclean

