<?php
#
# Назначение:
# Сохранение одного кортежа таблицы из базы данных
# Таблица:
# dmoz_sites
#
class TDmozSite
{
	//static $Site_ID_Index = 0;
	protected $Site_ID = 0;
	protected $Topic_ID = 0;
	protected $Title = "";
	protected $Passage = "";
	protected $URL = "";
	//-------------------------------------------------------------
	/**
	 * Конструктор (может при создании назначать номер топика)
	 *
	 * @param int
	 */
	public function __construct($topic_id = "")
	{
		/*$this->Site_ID = self :: $Site_ID_Index;
		self :: $Site_ID_Index++;*/
		if (is_int($topic_id))
		{
			$this->Topic_ID = $topic_id;
		}
	}
	//-------------------------------------------------------------
	/**
	 * Установка значений переменных членов класса
	 *
	 * @param int | string $value
	 */
	public function SetSiteID($value)
	{
		if (is_int($value))
		{
			$this->Site_ID = $value;
		}
	}
	public function SetTopicID($value)
	{
		if (is_int($value))
		{
			$this->Topic_ID = $value;
		}
	}
	public function SetTitle($value)
	{
		if (is_string($value))
		{
			$this->Title = $value;
		}
	}
	public function SetPassage($value)
	{
		if (is_string($value))
		{
			$this->Passage = $value;
		}
	}
	public function SetURL($value)
	{
		if (is_string($value))
		{
			$this->URL = $value;
		}
	}
	//-------------------------------------------------------------
	/**
	 * Возврат значения переменной Site_ID
	 *
	 * @return int
	 */
	public function GetSiteID()
	{
		return $this->Site_ID;
	}
	/**
	 * Возврат значения переменной Topic_ID
	 *
	 * @return int
	 */
	public function GetTopicID()
	{
		return  $this->Topic_ID;
	}
	/**
	 * Возврат значения переменной Title
	 *
	 * @return string
	 */
	public function GetTitle()
	{
		return $this->Title;
	}
	/**
	 * Возврат значения переменной Passage
	 *
	 * @return string
	 */
	public function GetPassage()
	{
		return $this->Passage;
	}
	/**
	 * Возврат значения переменной URL
	 *
	 * @return string
	 */
	public function GetURL()
	{
		return $this->URL;
	}
	//-------------------------------------------------------------
	/**
	 * Возврат строки всех параметров (для использования в sql запросе)
	 *
	 * @return unknown
	 */
	public function GetSQL()
	{
		return $this->Site_ID . ", " . $this->Topic_ID . ", '" . mysql_real_escape_string($this->Title) . "', '" . 
			   mysql_real_escape_string($this->Passage) . "', '" . mysql_real_escape_string($this->URL) . "'";
	}
}
//-------------------------------------------------------------
class TTempDmozSite extends TDmozSite
{
	protected $Topic_Name = "";
	protected $Rang = 0;
	protected $Topic_Resolv = false;
	protected $Expage_Resolv = false;
	//-------------------------------------------------------------
	public function SetTopicName($value)
	{
		if (is_string($value))
		{
			$this->Topic_Name = $value;
		}
	}
	//-------------------------------------------------------------
	public function SetRang($rang)
	{
		if (is_int($rang))
		{
			$this->Rang = $rang;
		}
	}
	//-------------------------------------------------------------
	public function SetTopicResolv($topic_resolv)
	{
		if (is_bool($topic_resolv))
		{
			$this->Topic_Resolv = $topic_resolv;
		}
	}
	//-------------------------------------------------------------
	public function SetExpageResolv($expage_resolv)
	{
		if (is_bool($expage_resolv))
		{
			$this->Expage_Resolv = $expage_resolv;
		}
	}
	//-------------------------------------------------------------
	public function GetTopicName()
	{
		return $this->Topic_Name;
	}
	//-------------------------------------------------------------
	public function GetRang()
	{
		return $this->Rang;
	}
	//-------------------------------------------------------------
	public function GetTopicResolv()
	{
		return $this->Topic_Resolv;
	}
	//-------------------------------------------------------------
	public function GetExpageResolv()
	{
		return $this->Expage_Resolv;
	}
	//-------------------------------------------------------------
	public function GetSQL()
	{
		return "'" . mysql_real_escape_string($this->Topic_Name) . "', '". mysql_real_escape_string($this->Title) . "', '" 
			. mysql_real_escape_string($this->Passage) . "', '" . mysql_real_escape_string($this->URL) . "', " . (int)$this->Rang  
			. ", " . (int)$this->Topic_Resolv . ", " . (int)$this->Expage_Resolv;
	}
	//-------------------------------------------------------------
}
?>