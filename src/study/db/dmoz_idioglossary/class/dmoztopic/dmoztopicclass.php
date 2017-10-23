<?php

/**
 * Сохранение одного кортежа таблицы dmoz_topic
 *
 */

class TDmozTopic
{
	//static $Topic_ID_Index = 0;
	protected $Topic_ID = 0;
	protected $Topic_Name = "";
	protected $Parent_ID = 0;
	//-------------------------------------------------------------
	/**
	 * Конструктор
	 *
	 */
	/*public function __construct()
	{
		$this->Topic_ID = self :: $Topic_ID_Index;
		self :: $Topic_ID_Index++;
	}*/
	//-------------------------------------------------------------
	/**
	 * Установка значений переменных членов класса
	 *
	 * @param int | string | empty
	 */
	public function SetTopicID($value)
	{
		if (is_int($value))
		{
			$this->Topic_ID = $value;
		}
	}
	public function SetTopicName($value)
	{
		if (is_string($value))
		{
			$this->Topic_Name = $value;
		}
	}
	public function SetParentID($value = 0)
	{
		if (is_int($value))
		{
			$this->Parent_ID = $value;
		}
		/*elseif ($value === false)
		{
			unset($this->Parent_ID);
		}*/
	}
	//------------------------------------------------------------
	/**
	 * Возврат значения переменной Topic_ID
	 *
	 * @return int
	 */
	public function GetTopicID()
	{
		return $this->Topic_ID;
	}
	/**
	 * Возврат значения переменной Topic_Name
	 *
	 * @return string
	 */
	public function GetTopicName()
	{
		return $this->Topic_Name;
	}
	/**
	 * Возврат значения переменной ParentID
	 *
	 * @return int
	 */
	public function GetParentID()
	{
		return $this->Parent_ID;
	}
	//-------------------------------------------------------------
	/**
	 * Возврат строки всех параметров (для использования в sql запросе)
	 *
	 * @return SQL
	 */
	public function GetSQL($topicrecord = false)
	{
		$temptopicid = "";
		if ((bool)$topicrecord === true)
		{
			$temptopicid = (string)$this->Topic_ID . ", ";
		}
		return (int)$temptopicid  . "'" . mysql_real_escape_string($this->Topic_Name) . "', " . (int)$this->Parent_ID;
	}
}
//------------------------------------------------------------------

/**
 * Дополнительные поля, которые требуются для временной таблицы temp_dmoz_topic
 *
 */
class TTempDmozTopic extends TDmozTopic 
{
	private $ParentName = "";
	private $Rang = 0;
	//-------------------------------------------------------------
	public function SetParentName($parentname)
	{
		if (is_string($parentname))
		{
			$this->ParentName = $parentname;
		}
	}
	//-------------------------------------------------------------
	public function SetRang($rang)
	{
		if (is_int($rang))
		{
			if ($rang == 1)
			{
			//	parent :: SetParentID(0);
				$this->ParentName = "";
			}
			$this->Rang = $rang;
		}
	}
	//-------------------------------------------------------------
	public function GetParentName()
	{
		return $this->GetParentName();
	}
	//-------------------------------------------------------------
	public function GetRang()
	{
		return  $this->Rang;	
	}
	//-------------------------------------------------------------
	public function GetSQL()
	{
		return "'" . mysql_real_escape_string($this->Topic_Name) . "', '". mysql_real_escape_string($this->ParentName) . "', " . (int)$this->Rang;
	}
}
?>