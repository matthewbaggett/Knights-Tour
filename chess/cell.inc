<?php

class Cell{
  private $_piece = null;
  private $_board = null;
  private $_x;
  private $_y;

  public function __construct(Board $board, $x, $y){
    $this->_board = $board;
    $this->_x = $x;
    $this->_y = $y;
  }

  public function get_x(){
    return $this->_x;
  }

  public function get_y(){
    return $this->_y;
  }

  /**
   * @param Piece $piece
   * @return $this
   */
  public function add_piece(Piece $piece){
    $this->_piece = $piece;
    return $this;
  }

  /**
   * @return Piece
   */
  public function get_piece(){
    return $this->_piece;
  }

  public function remove_piece(){
    $this->_piece = null;
  }

  /**
   * @return bool
   */
  public function is_occupied(){
    return $this->_piece instanceof Piece ? true : false;
  }

  public function get_move_options(){
    $moves = array();
    $potential_moves = $this->_piece->get_moves();
    foreach($potential_moves as $potential_move){
      $output_x = $potential_move[0] + $this->_x;
      $output_y = $potential_move[1] + $this->_y;
      if($output_x > $this->_board->get_width() || $output_x <= 0){
        continue;
      }
      if($output_y > $this->_board->get_height() || $output_y <= 0){
        continue;
      }
      $moves[] = array(
        'd_x' => $potential_move[0],
        'd_y' => $potential_move[1],
        'x' => $output_x,
        'y' => $output_y,
      );
    }
    return $moves;
  }
}