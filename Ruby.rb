#!/bin/env ruby

MAX_SWAP_PER_WORD = 2;
SWAP_PROBABILITY = 0.2;
MAX_REMOVE_PER_WORD = 0.2;
MAX_REMOVE_VOCAL = 0.05;
MAX_REMOVE_CONSONANT = 0.10;
MAX_REMOVE_DOUBLE = 0.40;
H_PROBABILITY = 0.3;


def rnd(prob)
	rand < prob
end

def letter?(char)
	char =~ /[[:alpha:]]/
end
def space?(char)
	char =~ /[[:space:]]/
end
def vocal?(char)
	['A', 'E', 'I', 'O', 'U'].include?(char)
end

def swap_letters(line)
	per_word = 0
	for i in 0..(line.size-1)
		c = line[i]
		if space?(c)
			per_word = 0
			next
		end
		if letter?(c) && letter?(line[i+1]) && per_word < MAX_SWAP_PER_WORD && rnd(SWAP_PROBABILITY)
			line[i], line[i+1] = line[i+1], line[i]
			per_word += 1
		end
	end
	line
end

def remove_letters(line)
    per_word = 0
    word_length = 0
    for i in 0..(line.size-1)
        c = line[i]
        
        if space?(c) || i == 0
            per_word = word_length = 0
            for j in (i ? i+1 : 0)..(line.size-1)
            	break unless letter? line[j]
            	word_length += 1
            end
        end

        skip = false
		
        if vocal?(c) && rnd(MAX_REMOVE_VOCAL)
            skip = true
        elsif c == line[i+1] && rnd(MAX_REMOVE_DOUBLE)
            skip = true
        elsif letter?(c) && !vocal?(c) && rnd(MAX_REMOVE_CONSONANT)
            skip = true
        end
        
        if skip && per_word < word_length*MAX_REMOVE_PER_WORD
            word_length -= 1
            line.slice! i
        end
    end
end

def add_h(line)
	if rnd(H_PROBABILITY)
		line.slice!(-1)
		line << " H!?"
	end
end

def process(line)
	line.upcase!
	swap_letters(line)
	remove_letters(line)
	add_h(line)
	line
end


file = ARGV.size > 0 ? File.open(ARGV[0], "r") : $stdin
file.each_line do |line|
	puts process(line)
end
file.close
