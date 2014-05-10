<?php
require_once("board.inc");
require_once("cell.inc");
require_once("piece.inc");
require_once("pieces/knight.inc");

define('TIME_BEGINS', microtime(true));

class Chess{
  protected $_board;
  protected $_solved = false;
  protected $_iteration = 0;

  public function __construct(){
    $this->_board = new Board(8,8);

  }

  public function run(){
    while($this->_solved == false){
      $this->__iterate();
    }
  }

  private function __iterate(){
    $time = number_format(microtime(true) - TIME_BEGINS, 4);
    echo "\r[{$time}] Iteration {$this->_iteration}";
    if(method_exists($this, 'iterate')){
      $this->iterate();
    }
    $this->_iteration++;
  }

  public function get_iteration_count(){
    return $this->_iteration;
  }
}