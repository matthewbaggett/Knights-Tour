<?php

class Piece{

  private $_id;
  private $_move_history = array();

  public function __construct(){
    $this->_id = uniqid();
  }

  public function get_id(){
    return $this->_id;
  }

  public function get_type(){
    return str_replace("Piece", "", get_called_class());
  }

  public function add_move_history($x, $y){
    $this->_move_history[] = array('x' => $x, 'y' => $y);
  }

  public function get_move_history(){
    return $this->_move_history;
  }

  public function is_in_move_history($x, $y){
    if(count($this->_move_history) > 0){
      foreach($this->_move_history as $move_history){
        if($move_history['x'] == $x && $move_history['y'] == $y){
          return true;
        }
      }
      return false;
    }
    return false;
  }
}