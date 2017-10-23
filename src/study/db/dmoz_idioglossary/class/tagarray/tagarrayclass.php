<?php
//--------------------------------------------------------------------
require_once('tagarraydefine.php');
//--------------------------------------------------------------------
/**
 * Класс, формально реализующий стек
 * Необходим для конроля закрывающих и открывающих тегов 
 */

class TTagArray
{
	private $Tags = array();
	private $Counter = 0;
	private $IgnoreFlag = false;
	private $IgnoreIndex = 0;
	//--------------------------------------
	/**
	 * Добавление одного тега в конец списка
	 *
	 * @param string $value
	 */
	public function AddTag($value, $ignoreflag = false)
	{
		if (is_string($value) && trim((string)$value) != "")
		{
			$this->Tags[$this->Counter] = $value;
			$this->Counter++;
			if ((!$this->IgnoreFlag) && ($ignoreflag === true))
			{
				$this->IgnoreIndex = $this->Counter - 1;
				$this->IgnoreFlag = true;
			}
		}
	}
	//--------------------------------------
	/**
	 * Возврат значения тега (вершины, конкретного или пустой строки, если стек пуст)
	 *
	 * @param unsinged int $value
	 * 
	 * @return string
	 */
	public function GetTag($value = false)
	{
		if (($value === false) && ($this->Counter > 0))
		{
			return $this->Tags[$this->Counter - 1];
		}
		elseif (is_int($value) && ($value >= 0) && ($value < $this->Counter))
		{
			return $this->Tags[$value];
		}
		else 
		{
			return "";
		}
	}
	//--------------------------------------
	/**
	 * Удаление вершины стека тегов
	 *
	 * @param unknown_type $name
	 */
	public function RemoveTag($name = "")
	{
		if ($this->Counter !== 0)
		{
			if ((strcmp($name, "") === 0) || (strcmp($name, $this->Tags[$this->Counter - 1]) === 0))
			{
				if ($this->Counter - 1 == $this->IgnoreIndex)
				{	
					$this->IgnoreFlag = false;
				}	
				unset($this->Tags[--$this->Counter]);
			}
			else 
			{
				throw new Exception(TAGNOTSIMMETRIC, 0);
			}
		}
	}
	//--------------------------------------
	/**
	 * Возврат количества элементов
	 *
	 * @return int
	 */
	public function GetCounter()
	{
		return $this->Counter;
	}
	//--------------------------------------
	/**
	 * Возвращает значение флага игнорирования
	 *
	 * @return bool
	 */
	public function GetIgnoreFlag()
	{
		return $this->IgnoreFlag;
	}
	//---------------------------------------
	/**
	 * Устанавливает значение флага игнорирования
	 *
	 * @param int $position
	 */
	public function SetIgnoreFlag($position = false)
	{
		if (($this->Counter > 0) && (!$this->IgnoreFlag))
		{
			if ($position === false)
			{
				$this->IgnoreIndex = $this->Counter - 1;
				$this->IgnoreFlag = true;
			}
			elseif (is_int($position) && $position < $this->Counter)
			{
				$this->IgnoreIndex = $position;
				$this->IgnoreFlag = true;
			}
		}
	}
}
?>