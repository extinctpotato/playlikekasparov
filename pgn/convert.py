#!/usr/bin/env python3

import chess, chess.pgn, sys, os

pgn = open(sys.argv[1])

game = None

for i in range(int(sys.argv[2])):
    game = chess.pgn.read_game(pgn)

board = game.board()

for move in game.mainline_moves():
    board.push(move)
    print(board)
    print('\n')
