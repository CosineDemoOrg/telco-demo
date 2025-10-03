/*
 * Copyright (C) 2025 by Cosine
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "cdr.h"
#include "ogs-core.h"
#include <stdio.h>

static const char *smf_cdr_path(void)
{
    const char *env = getenv("OPEN5GS_SMF_CDR_PATH");
    if (env && *env)
        return env;
    return "/var/log/open5gs/smf-cdr.jsonl";
}

void smf_cdr_write_usage(smf_sess_t *sess, const char *event)
{
    char ipv4_str[OGS_ADDRSTRLEN] = "";
    char ipv6_str[OGS_ADDRSTRLEN] = "";
    const char *supi = NULL;
    const char *imsi = NULL;
    const char *dnn = NULL;
    const char *path = NULL;
    FILE *fp = NULL;
    ogs_time_t now = ogs_time_now();

    ogs_assert(sess);

    if (sess->ipv4)
        OGS_INET_NTOP(&sess->ipv4->addr, ipv4_str);
    if (sess->ipv6)
        OGS_INET6_NTOP(&sess->ipv6->addr, ipv6_str);

    {
        smf_ue_t *ue = smf_ue_find_by_id(sess->smf_ue_id);
        if (ue) {
            supi = ue->supi;
            imsi = ue->imsi_bcd;
        }
    }

    dnn = sess->session.name;

    path = smf_cdr_path();
    fp = fopen(path, "a");
    if (!fp) {
        ogs_error("Failed to open CDR file %s", path);
        return;
    }

    /* Write one JSON object per line (JSON Lines) */
    fprintf(fp,
        "{\"ts\":%lld,"
        "\"event\":\"%s\","
        "\"supi\":\"%s\","
        "\"imsi\":\"%s\","
        "\"psi\":%u,"
        "\"dnn\":\"%s\","
        "\"ue_ip_v4\":\"%s\","
        "\"ue_ip_v6\":\"%s\","
        "\"ul_octets\":%llu,"
        "\"dl_octets\":%llu,"
        "\"duration\":%lld,"
        "\"reporting_reason\":%u,"
        "\"up_cnx_state\":%d"
        "}\n",
        (long long)now,
        event ? event : "usage_report",
        supi ? supi : "",
        imsi ? imsi : "",
        sess->psi,
        dnn ? dnn : "",
        ipv4_str,
        ipv6_str,
        (unsigned long long)sess->gy.ul_octets,
        (unsigned long long)sess->gy.dl_octets,
        (long long)sess->gy.duration,
        sess->gy.reporting_reason,
        sess->up_cnx_state
    );

    fclose(fp);
}