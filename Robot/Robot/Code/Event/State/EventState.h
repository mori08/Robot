#pragma once


namespace Robot
{
	/*
	EventStateクラス
	EventManagerにおける状態
	*/
	class EventState
	{
	public:

		/// <summary>
		/// 更新
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const = 0;

	};
}