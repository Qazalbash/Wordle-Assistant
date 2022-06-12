import random


class Wordle:

    def __init__(self, filename: str) -> None:
        self.words = list()
        self.readfile(filename)
        self.map = {i: set([chr(j) for j in range(97, 123)]) for i in range(5)}
        self.allowed = set()

    def readfile(self, filename: str) -> None:
        with open(filename, 'r') as file:
            self.words = [word[:-1] for word in file]
        self.all_words = self.words

    def evalute_guess(self, guess: str, color: str) -> None:
        for i in range(5):
            if color[i] == 'g':
                self.map[i] = set([guess[i]])
                self.allowed.add(guess[i])
            elif color[i] == 'y':
                self.map[i] = self.map.get(i).difference(guess[i])
                self.allowed.add(guess[i])
            elif guess[i] in self.allowed:
                self.map[i] = self.map.get(i).difference(guess[i])
            else:
                for j in range(5):
                    self.map[j] = self.map.get(j).difference(guess[i])

    def valid_word(self, word: str) -> bool:
        for i in range(5):
            if word[i] not in self.map[i]:
                return False
        for j in self.allowed:
            if j not in word:
                return False
        return True

    def possible_words(self) -> None:
        self.words = [word for word in self.words if self.valid_word(word)]

    def turn(self, num: int) -> None:
        print("\nTURN NO:", num)

        guess = random.choice(self.words)

        print("\nTRY WORD:", guess)

        color = input("\nEnter the colors: ")

        self.evalute_guess(guess, color)
        self.possible_words()


if __name__ == '__main__':
    w = Wordle('./allowed_words.txt')
    for i in range(1, 7):
        w.turn(i)
