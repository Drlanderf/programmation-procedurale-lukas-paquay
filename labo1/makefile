CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
TARGET = dev-profile

SRC = main.c \
      profil/profil.c \
      competences/competences.c \
      projets/projets.c \
      statistiques/statistiques.c

OBJ = $(SRC:.c=.o)
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)
main.o: main.c profil/profil.h competences/competences.h projets/projets.h statistiques/statistiques.h
	$(CC) $(CFLAGS) -c $< -o $@
profil/profil.o: profil/profil.c profil/profil.h
	$(CC) $(CFLAGS) -c $< -o $@
competences/competences.o: competences/competences.c competences/competences.h
	$(CC) $(CFLAGS) -c $< -o $@
projets/projets.o: projets/projets.c projets/projets.h
	$(CC) $(CFLAGS) -c $< -o $@
statistiques/statistiques.o: statistiques/statistiques.c statistiques/statistiques.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET)
re: clean all
run: $(TARGET)
	./$(TARGET)
.PHONY: all clean re run
