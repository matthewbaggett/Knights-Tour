<?php

class PieceKnight extends Piece{
  public function get_moves(){
    return array(
      array(+1,+2),
      array(+2,+1),
      array(-1,+2),
      array(-2,+1),
      array(+1,-2),
      array(+2,-1),
      array(-1,-2),
      array(-2,-1),
    );
  }
}