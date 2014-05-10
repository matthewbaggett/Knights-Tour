<?php

class Board{
  private $_grid;
  private $_width = 8;
  private $_height = 8;

  public function __construct($width = 8, $height = 8){
    $this->_width = $width;
    $this->_height = $height;
    for($x = 1; $x <= $this->_width; $x++){
      for($y = 1; $y <= $this->_height; $y++){
        $this->_grid[$x][$y] = new Cell($this, $x, $y);
      }
    }
  }

  public function get_width(){
    return $this->_width;
  }

  public function get_height(){
    return $this->_height;
  }

  /**
   * @param Piece $piece
   * @param $x
   * @param $y
   * @return Cell
   * @throws Exception
   */
  public function add_piece(Piece $piece, $x, $y){
    /* @var $selected_cell Cell */
    if(!isset($this->_grid[$x][$y])){
      throw new Exception("Cell does not exist.");
    }
    $selected_cell = $this->_grid[$x][$y];
    if($selected_cell->is_occupied()){
      throw new Exception("Cell is already full");
    }
    //echo " > Adding Piece {$piece->get_type()} to board at {$x},{$y}\n";
    return $selected_cell->add_piece($piece);
  }

  public function find_piece(Piece $piece){
    foreach($this->_grid as $x => $col){
      foreach($col as $y => $cell){
        /* @var $cell Cell */
        if($cell->is_occupied()){
          if($cell->get_piece()->get_id() == $piece->get_id()){
            return $cell;
          }
        }
      }
    }
  }

  public function move_piece(Piece $piece, $x, $y){
    // Find piece
    $cell = $this->find_piece($piece);

    // Check location is empty.
    if(!$this->is_cell_empty($x,$y)){
      throw new Exception("Cannot move to {$x},{$y} destination is blocked by another piece");
    }

    // Move piece to new location
    $this->_move_piece($piece, $x, $y);
  }

  public function is_cell_empty($x, $y){
    return !$this->is_cell_full($x, $y);
  }

  public function is_cell_full($x, $y){
    $cell = $this->_grid[$x][$y];
    if(!$cell instanceof Cell){
      echo " > {$x}, {$y} isn't a cell apparently";
    }
    return $cell->is_occupied();
  }

  private function _move_piece(Piece $piece, $x, $y){
    $old_cell = $this->find_piece($piece);
    $this->_grid[$x][$y]->add_piece($piece);
    $this->_grid[$old_cell->get_x()][$old_cell->get_y()]->remove_piece();

    $piece->add_move_history($x,$y);

    $new_cell = $this->find_piece($piece);
    //echo " > Moved {$piece->get_type()} from {$old_cell->get_x()},{$old_cell->get_y()} to {$new_cell->get_x()},{$new_cell->get_y()}\n";
    return $new_cell;
  }
}