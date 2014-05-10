<?php

require_once('chess/chess.inc');

class KnightsTourNoMoreMovesException extends Exception{}
class KnightsTour extends Chess{
  private $_knight;

  public function __construct(){
    parent::__construct();
    $this->_knight = new PieceKnight();
    $this->_board->add_piece($this->_knight, rand(1,$this->_board->get_width()), rand(1, $this->_board->get_height()));
  }

  public function iterate(){
    // Find the Knight.
    $cell = $this->_board->find_piece($this->_knight);

    // Decide where it can move
    $move_options = $cell->get_move_options();

    // Decide if its been there before TODO
    $valid_move_options = array();
    foreach($move_options as $i => $move_option){
      if(!$this->_knight->is_in_move_history($move_option['x'], $move_option['y'])){
        $valid_move_options[] = $move_option;
      }
    }


    // If no move options, end iteration.
    if(count($valid_move_options) == 0){
      throw new KnightsTourNoMoreMovesException('No more moves');
    }

    // Choose an option at random.
    $solution = $valid_move_options[rand(0,count($valid_move_options)-1)];
    // Move the Knight

    $this->_board->move_piece($this->_knight, $solution['x'], $solution['y']);
  }

  public function get_iteration_limit(){
    return $this->_board->get_width() * $this->_board->get_height();
  }
}

class Cycler{
  private $_start_microtime;

  public function __construct(){
    $this->_start_microtime = microtime(true);
  }

  public function run($callback){
    $persist = array();
    while(true){
      $callback($persist);
    }
  }
}

$cyc = new Cycler();
$cyc->run(function(&$persist){
  $kt = new KnightsTour();
  try{
    $kt->run();
  }catch(KnightsTourNoMoreMovesException $e){
    $persist['max_iterations'] = $kt->get_iteration_count() > $persist['max_iterations'] ? $kt->get_iteration_count() : $persist['max_iterations'];
    echo " > Ran out of moves after {$kt->get_iteration_count()} iterations. Record so far: {$persist['max_iterations']}/{$kt->get_iteration_limit()}\n";
  }
});