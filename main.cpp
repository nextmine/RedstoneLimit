#include <Neutron2/Logger.h>
#include <Neutron2/mc/world/BlockSource.hpp>
#include <Neutron2/mc/redstone/CircuitSystem.hpp>

// Мы рекомендуем использовать глобальный логгер.
extern Logger logger;
extern Neutron2::Version PLUGIN_VERSION;

// Глобальные переменные для хранения текущих значений тиков
unsigned float LTick;
unsigned float CTick;

// Лимит тиков
LTick = Neutron2::MaxTicks * 0.5;

// Хук для ограничения частоты редстоуна
TInstanceHook(void, Event::CircuitUpdate, CircuitSystem, BlockSource *bs) {
  if (!LTick) return original(this, bs); // Если LTick равен 0, то ограничение не применяется
  CTick++; // Увеличиваем текущий счетчик тиков
  if (CTick % LTick == 0) { // Если текущий тик делится на LTick без остатка, выполняем обновление редстоуна
    CTick = 0;
    return original(this, bs);
  }
}
