# Read two words from the user
word1 = input("First word: ").strip()
word2 = input("Second word: ").strip()

# Convert both words to lowercase to avoid case mismatch
word1 = word1.lower()
word2 = word2.lower()

# Check if they are the same length and have the same sorted letters
if len(word1) == len(word2) and sorted(word1) == sorted(word2):
    print("Given words are anagrams.")
else:
    print("Given words are not anagrams.")
