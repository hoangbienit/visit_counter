<?php

/**
 * Implements of hook_block_info().
 */
function visit_counter_block_info() {
  $blocks = array();
  $blocks[0]['info'] = t('Visit counter');
  $blocks[0]['cache'] = DRUPAL_NO_CACHE;

  return $blocks;
}

/**
 * Implements of hook_block_view().
 */
function visit_counter_block_view($delta = '') {
  $data = array();
  $data['subject'] = t('Visit counter');
  $data['content'] = theme_visit_counter_block_view();

  return $data;
}

/**
*	Implement a theme function for block output.
*/
function theme_visit_counter_block_view() {
  $list_items = array();

  visit_counter_block_show_day($list_items);
  visit_counter_block_show_last_day($list_items);
  visit_counter_block_show_week($list_items);
  visit_counter_block_show_last_week($list_items); 
  visit_counter_block_show_month($list_items);
  visit_counter_block_show_year($list_items);
  visit_counter_block_show_total($list_items);
  $list_items[] = '<a href="http://thanhlapweb.net" target="_blank">www.ThanhLapWeb.net</a>';

  return theme('item_list', array('items' => $list_items, 'type' => 'ul'));
}

/**
 * Display total visitors count to visitors block.
 *
 * @param $list_items
 *   array associative array of variables, use for theme function
 */

function visit_counter_block_show_day(&$list_items){
	if(variable_get('visit_counter_block_show_day', 1)){
		$start_count = variable_get('visit_counter_start_count_day', 0);
		
		$results = db_select('visit_counter', 'v')
		->fields('v', array('count(v.last_visit)'))
		->where('DAY(FROM_UNIXTIME(v.last_visit)) = DAY(CURDATE())')		
		->where('MONTH( FROM_UNIXTIME(v.last_visit)) = MONTH(CURDATE())')
		->where('YEAR(FROM_UNIXTIME(v.last_visit)) = YEAR(CURDATE())')
		->countQuery()
		->execute()
		->fetchField();		
		$count = $results + $start_count;
				
		$list_items[] = sprintf('%s: %d', t('Today'), $count);
	}
}

function visit_counter_block_show_last_day(&$list_items){
	if(variable_get('visit_counter_block_show_last_day', 1)){
		$start_count = variable_get('visit_counter_start_count_last_day', 0);
		
		$results = db_select('visit_counter', 'v')
		->fields('v', array('count(last_visit)'))
		->where('DAY(FROM_UNIXTIME(v.last_visit)) = DAY(CURRENT_DATE - INTERVAL 1 DAY)')
		->countQuery()
		->execute()
		->fetchField();		
		$count = $results + $start_count;
		
		$list_items[] = sprintf('%s: %d', t('Last Day'), $count);
	}
}

function visit_counter_block_show_week(&$list_items){
	if(variable_get('visit_counter_block_show_week', 1)){
		$start_count = variable_get('visit_counter_start_count_week', 0);
		
		$results = db_select('visit_counter', 'v')
		->fields('v', array('count(last_visit)'))
		->where('WEEK( FROM_UNIXTIME(v.last_visit)) = WEEK(CURDATE())')		
		->where('MONTH( FROM_UNIXTIME(v.last_visit)) = MONTH(CURDATE())')
		->where('YEAR(FROM_UNIXTIME(v.last_visit)) = YEAR(CURDATE())')
		->countQuery()
		->execute()
		->fetchField();		
		$count = $results + $start_count;
		
		$list_items[] = sprintf('%s: %d', t('This Week'), $count);
	}
}

function visit_counter_block_show_last_week(&$list_items){
	if(variable_get('visit_counter_block_show_last_week', 1)){
		$start_count = variable_get('visit_counter_start_count_last_week', 0);
		
		$results = db_select('visit_counter', 'v')
		->fields('v', array('count(last_visit)'))
		->where('YEARWEEK(FROM_UNIXTIME(v.last_visit)) = YEARWEEK(CURRENT_DATE - INTERVAL 7 DAY)')
		->countQuery()
		->execute()
		->fetchField();		
		$count = $results + $start_count;
		
		$list_items[] = sprintf('%s: %d', t('Last Week'), $count);
	}
}

function visit_counter_block_show_month(&$list_items){
	if(variable_get('visit_counter_block_show_month', 1)){
		$start_count = variable_get('visit_counter_start_count_month', 0);
		
		$results = db_select('visit_counter', 'v')
		->fields('v', array('count(last_visit)'))
		->where('MONTH( FROM_UNIXTIME(v.last_visit)) = MONTH(CURDATE())')
		->where('YEAR(FROM_UNIXTIME(v.last_visit)) = YEAR(CURDATE())')
		->countQuery()
		->execute()
		->fetchField();		
		$count = $results + $start_count;
		
		$list_items[] = sprintf('%s: %d', t('This Month'), $count);
	}
}

function visit_counter_block_show_year(&$list_items){
	if(variable_get('visit_counter_block_show_year', 1)){
		$start_count = variable_get('visit_counter_start_count_year', 0);
		
		$results = db_select('visit_counter', 'v')
		->fields('v', array('count(last_visit)'))
		->where('YEAR(FROM_UNIXTIME(v.last_visit)) = YEAR(CURDATE())')
		->countQuery()
		->execute()
		->fetchField();
		$count = $results + $start_count;
		$list_items[] = sprintf('%s: %d', t('This Year'), $count);
	}
}
 
function visit_counter_block_show_total(&$list_items) {
  if (variable_get('visit_counter_block_show_total', 1)) {
    $start_count = variable_get('visit_counter_start_count_total', 0);
	
	$results = db_select('visit_counter', 'v')
		->fields('v', array('count(visitor_id)'))
		->countQuery()
		->execute()
		->fetchField();
	$count = $results + $start_count;
    $list_items[] = sprintf('%s: %d', t('Total'), $count);
  }
}