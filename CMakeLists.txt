cmake_minimum_required(VERSION 3.7)
project(five)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES AI-easy.c AI-middle.c display.c FirstPiece.c five_piece.c five_piece.h getaddress.c JudgeWin02.c PieceInfor.c PlusScore.c pvc.c pvp.c score.c type.c)

add_executable(five ${SOURCE_FILES})