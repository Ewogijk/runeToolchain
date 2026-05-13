#ifndef EMBER_MEMORYBITS_H
#define EMBER_MEMORYBITS_H

#include <Ember/Enum.h>

namespace Ember {
    /**
     * @brief Page protection define how memory can be interacted with.
     * <ul>
     *  <li>READ: The pages will be readonly.</li>
     *  <li>WRITE: The pages will be readable and writable.</li>
     * </ul>
     */
#define PAGE_PROTECTIONS(X)             \
         X(PageProtection, READ, 0x1)   \
         X(PageProtection, WRITE, 0x2)


    DECLARE_ENUM(PageProtection, PAGE_PROTECTIONS, 0x0) // NOLINT

}

#endif //EMBER_MEMORYBITS_H
