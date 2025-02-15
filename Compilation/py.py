def compute_first(grammar):
    first = {nonterminal: set() for nonterminal in grammar}
    
    while True:
        updated = False
        for nonterminal, productions in grammar.items():
            for production in productions:
                current_size = len(first[nonterminal])
                
                if not production:  # epsilon
                    first[nonterminal].add('ε')
                elif not production[0].isupper():  # terminal
                    first[nonterminal].add(production[0])
                else:  # nonterminal
                    can_be_empty = True
                    for symbol in production:
                        if not symbol.isupper():  # terminal
                            first[nonterminal].add(symbol)
                            can_be_empty = False
                            break
                        first[nonterminal].update(first[symbol] - {'ε'})
                        if 'ε' not in first[symbol]:
                            can_be_empty = False
                            break
                    if can_be_empty:
                        first[nonterminal].add('ε')
                
                if len(first[nonterminal]) > current_size:
                    updated = True
        
        if not updated:
            break
    
    return first

def compute_follow(grammar, first):
    follow = {nonterminal: set() for nonterminal in grammar}
    follow['S'].add('$')  # Add $ to start symbol
    
    while True:
        updated = False
        for nonterminal, productions in grammar.items():
            for production in productions:
                trailer = follow[nonterminal]
                for symbol in reversed(production):
                    if symbol.isupper():  # nonterminal
                        current_size = len(follow[symbol])
                        follow[symbol].update(trailer)
                        if len(follow[symbol]) > current_size:
                            updated = True
                        if 'ε' in first[symbol]:
                            trailer = trailer.union(first[symbol] - {'ε'})
                        else:
                            trailer = first[symbol]
                    else:  # terminal
                        trailer = {symbol}
        
        if not updated:
            break
    
    return follow

# Test with your grammar
grammar = {
    'S': ['acB',""],  # empty string represents ε
    'B': ['Saa', 'b'],
}

first_sets = compute_first(grammar)
follow_sets = compute_follow(grammar, first_sets)

for nt, firsts in first_sets.items():
    if firsts:  # Check if the set is not empty
        print(f'FIRST({nt}) = {firsts}')

print("\nFOLLOW Sets:")
for nt, follows in follow_sets.items():
    if follows:  # Check if the set is not empty
        print(f'FOLLOW({nt}) = {follows}')